///////////////////////////////////////////////////////////////////////////////
/// @file OpenGL_Programme.cpp
///
/// @author Martin Paradis
/// @date 2014-08-28
///
/// @addtogroup opengl OpenGL
/// @{
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>
#include <algorithm>

#include "gl\glew.h"
#include "OpenGL_Programme.h"
#include "OpenGL_Nuanceur.h"
#include "OpenGL_Debug.h"
#include "glm\glm.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace opengl{

	GLuint Programme::programmeActif{ PROGRAMME_INVALIDE };

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn Programme::Programme(Programme&& programme)
	///
	/// Constructeur par transfert ("move") en utilisant l'assignation par
	/// transfert
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	Programme::Programme(Programme&& programme)
	{
		*this = std::move(programme);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn Programme& Programme::operator=(Programme&& programme)
	///
	/// Transfère la propriété du programme reçu en paramètre et s'assure
	/// que ce dernier ne libérera pas son identifiant opengl lors de sa 
	/// destruction.
	///
	/// @return Le présent programme
	///
	////////////////////////////////////////////////////////////////////////
	Programme& Programme::operator=(Programme&& programme)
	{
		/// Libérer l'identifiant courant, si nécessaire
		relacher();

		/// récupérer les données de l'autre programme
		handle_ = programme.handle_;
		programme.handle_ = PROGRAMME_INVALIDE;
		mapUniforme = std::move(programme.mapUniforme);
		nuanceursAttaches = std::move(programme.nuanceursAttaches);
		flags = programme.flags;
		nom_ = std::move(programme.nom_);
		programme.relacher();

		return *this;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn Programme::~Programme()
	///
	/// Destructeur, ne fait que relâcher l'identifiant OpenGL et remettre
	/// les données à leur valeur initiale.
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	Programme::~Programme()
	{
		relacher();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Programme::relacher()
	///
	/// Relâche l'identifiant OpenGL et remet les données à leur valeur initiale.
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	void Programme::relacher()
	{
		if (handle_ != PROGRAMME_INVALIDE)
		{
			glDeleteProgram(handle_);
		}
		handle_ = PROGRAMME_INVALIDE;
		mapUniforme.clear();
		nuanceursAttaches.clear();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Programme::initialiser()
	///
	/// Crée un identifiant OpenGL pour le programme.
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	void Programme::initialiser()
	{
		/// Make sure resource is not left unused
		relacher();
		handle_ = glCreateProgram();
		flags.estInitialise = (handle_ != PROGRAMME_INVALIDE);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Programme::attacherNuanceur(const opengl::Nuanceur& shader)
	///
	/// Attache un nuanceur au programme.
	///
	/// @param[in] nuanceur : le nuanceur à attacher au programme
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	void Programme::attacherNuanceur(const opengl::Nuanceur& nuanceur)
	{
		/// Attacher le nuanceur si le programme a été créé et si le 
		/// nuanceur n'est pas déjà attaché
		if (flags.estInitialise &&
			std::find(std::begin(nuanceursAttaches), std::end(nuanceursAttaches), nuanceur.obtenirNom()) == nuanceursAttaches.end())
		{
			glAttachShader(handle_, nuanceur.obtenirHandle());
			nuanceursAttaches.push_back(nuanceur.obtenirNom());
			/// Nécessite d'être lier à nouveau
			flags.estLie = false;
			flags.estValide = false;
		}
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Programme::detacherNuanceur(const opengl::Nuanceur& shader)
	///
	/// Detache un nuanceur au programme.
	///
	/// @param[in] nuanceur : le nuanceur à détacher au programme
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	void Programme::detacherNuanceur(const opengl::Nuanceur& shader)
	{
		/// Détacher seulement si le nuanceur est attaché
		if (std::find(std::begin(nuanceursAttaches), std::end(nuanceursAttaches), shader.obtenirNom()) != nuanceursAttaches.end())
		{
			nuanceursAttaches.erase(std::remove(std::begin(nuanceursAttaches), std::end(nuanceursAttaches), shader.obtenirNom()), std::end(nuanceursAttaches));
			glDetachShader(handle_, shader.obtenirHandle());
			/// Nécessite d'être lier à nouveau
			flags.estLie = false;
			flags.estValide = false;
		}
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Programme::lier()
	///
	/// Permet de lier le programme.
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	void Programme::lier()
	{
		/// Ne pas lier le programme sans nécéssité
		if (flags.estLie || !flags.estInitialise)
			return;

		/// La location des uniformes ne sont plus valides, on les flush
		mapUniforme.clear();

		glLinkProgram(handle_);

		/// Vérifier le status de la liaison
		GLint LinkStatus{ 0 };
		glGetProgramiv(handle_, GL_LINK_STATUS, &LinkStatus);
		flags.estLie = (LinkStatus == GL_TRUE);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Programme::valider()
	///
	/// Permet de valider le programme.
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	void Programme::valider()
	{
		/// Ne pas valider sans nécéssité
		if (flags.estValide || !flags.estLie)
			return;

		glValidateProgram(handle_);

		/// Vérifier le status de la validité
		GLint validationStatus{ 0 };
		glGetProgramiv(handle_, GL_VALIDATE_STATUS, &validationStatus);
		flags.estValide = (validationStatus == GL_TRUE);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Programme::Start(Programme& programme)
	///
	/// Permet de commencer l'utilisation d'un programme.
	///
	/// @param[in] : programme : le programme à utiliser.
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	void Programme::Start(Programme & programme)
	{
		/// Ne pas repartir le même programme
		if (programmeActif == programme.handle_ && programme.flags.estValide)
			return;

		/// Lier et valider le programme
		programme.lier();
		programme.valider();
		/// Ne pas partir un programme invalide
		programmeActif = programme.flags.estValide ? programme.handle_ : PROGRAMME_INVALIDE;
		glUseProgram(programmeActif);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Programme::Stop(Programme& programme)
	///
	/// Permet de cesser l'utilisation d'un programme.
	///
	/// @param[in] : programme : le programme à cesser.
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	void Programme::Stop(Programme const& programme)
	{
		/// Ne pas cesser l'utilisation d'un programme s'il n'est pas utilisé
		if (programmeActif != programme.handle_)
			return;

		programmeActif = PROGRAMME_INVALIDE;
		glUseProgram(programmeActif);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool Programme::recupererLocationUniforme(std::string attribute_name)
	///
	/// Permet de récupérer la location d'un uniforme dans les nuanceurs.
	///
	/// @param[in] : attribute_name : le nom de l'uniforme.
	///
	/// @return Vrai si la location a été récupérée, faux sinon.
	///
	////////////////////////////////////////////////////////////////////////
	bool Programme::recupererLocationUniforme(std::string attribute_name)
	{
		/// Si la location n'est pas déjà trouvée
		if (mapUniforme.find(attribute_name) == mapUniforme.end())
		{
			/// L'obtenir
			GLint uniform{ glGetUniformLocation(handle_, attribute_name.c_str()) };
			if (uniform == -1)
			{
				/// La location de l'uniforme n'a pu être trouvée
				return false;
			}
			else
			{	/// Conserver la location de l'uniforme
				mapUniforme[attribute_name] = uniform;
			}
		}
		return true;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn std::string Programme::serialiser() const
	///
	/// Permet d'obtenir une chaine de caractère représentant l'état du 
	/// programme.
	///
	/// @return La chaine de caractère représentant l'état du programme.
	///
	////////////////////////////////////////////////////////////////////////
	std::string Programme::serialiser() const
	{
		std::stringstream programme;
		programme
			<< '\n'
			<< "Programme : " << '\n'
			<< '\t' << nom_ << '\n'
			<< "handle : " << '\n'
			<< '\t';

		flags.estInitialise ? programme << handle_ : programme << "Non-initialise";
		programme << '\n';

		programme
			<< "Nuanceurs attaches : " << '\n';
		if (!nuanceursAttaches.empty())
		{
			for (std::string const& shader_name : nuanceursAttaches)
			{
				programme << '\t' << shader_name << '\n';
			}
		}
		else
		{
			programme << '\t' << "Aucun" << '\n';
		}

		programme << "uniforme map :" << '\n';
		if (!mapUniforme.empty())
		{
			for (auto const& elem : mapUniforme)
			{
				programme << '\t' << "{ " << "uniforme location: " << elem.second << ", nom : " << elem.first << " }" << '\n';
			}
		}
		else
		{
			programme << '\t' << "Aucun" << '\n';
		}

		programme << "Validite : " << '\n';
		if (flags.estValide)
		{
			programme << '\t' << "valide.";
		}
		else
		{
			programme << '\t' << (flags.estLie ? "invalide." : flags.estInitialise ? "non-lie." : "non-initialise.");
		}

		programme << '\n';
		return programme.str();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, int const& uniform_value)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_value : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, int const& uniform_value)
	{
		glProgramUniform1i(handle_, mapUniforme[attribute_name], uniform_value);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::ivec2 const& uniform_vector)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_vector : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::ivec2 const& uniform_vector)
	{
		glProgramUniform2iv(handle_, mapUniforme[attribute_name], 1, glm::value_ptr(uniform_vector));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::ivec3 const& uniform_vector)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_vector : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::ivec3 const& uniform_vector)
	{
		glProgramUniform3iv(handle_, mapUniforme[attribute_name], 1, glm::value_ptr(uniform_vector));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::ivec4 const& uniform_vector)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_vector : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::ivec4 const& uniform_vector)
	{
		glProgramUniform4iv(handle_, mapUniforme[attribute_name], 1, glm::value_ptr(uniform_vector));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, unsigned int const& uniform_value)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_value : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, unsigned int const& uniform_value)
	{
		glProgramUniform1ui(handle_, mapUniforme[attribute_name], uniform_value);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::uvec2 const& uniform_vector)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_vector : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::uvec2 const& uniform_vector)
	{
		glProgramUniform2uiv(handle_, mapUniforme[attribute_name], 1, glm::value_ptr(uniform_vector));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::uvec3 const& uniform_vector)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_vector : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::uvec3 const& uniform_vector)
	{
		glProgramUniform3uiv(handle_, mapUniforme[attribute_name], 1, glm::value_ptr(uniform_vector));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::uvec4 const& uniform_vector)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_vector : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::uvec4 const& uniform_vector)
	{
		glProgramUniform4uiv(handle_, mapUniforme[attribute_name], 1, glm::value_ptr(uniform_vector));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, float const& uniform_value)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_value : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, float const& uniform_value)
	{
		glProgramUniform1f(handle_, mapUniforme[attribute_name], uniform_value);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::vec2 const& uniform_vector)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_vector : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::vec2 const& uniform_vector)
	{
		glProgramUniform2fv(handle_, mapUniforme[attribute_name], 1, glm::value_ptr(uniform_vector));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::vec3 const& uniform_vector)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_vector : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::vec3 const& uniform_vector)
	{
		glProgramUniform3fv(handle_, mapUniforme[attribute_name], 1, glm::value_ptr(uniform_vector));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::vec4 const& uniform_vector)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_vector : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::vec4 const& uniform_vector)
	{
		glProgramUniform4fv(handle_, mapUniforme[attribute_name], 1, glm::value_ptr(uniform_vector));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, double const& uniform_value)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_value : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, double const& uniform_value)
	{
		glProgramUniform1d(handle_, mapUniforme[attribute_name], uniform_value);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::dvec2 const& uniform_vector)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_vector : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::dvec2 const& uniform_vector)
	{
		glProgramUniform2dv(handle_, mapUniforme[attribute_name], 1, glm::value_ptr(uniform_vector));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::dvec3 const& uniform_vector)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_vector : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::dvec3 const& uniform_vector)
	{
		glProgramUniform3dv(handle_, mapUniforme[attribute_name], 1, glm::value_ptr(uniform_vector));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::dvec4 const& uniform_vector)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_vector : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::dvec4 const& uniform_vector)
	{
		glProgramUniform4dv(handle_, mapUniforme[attribute_name], 1, glm::value_ptr(uniform_vector));
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::mat2 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::mat2 const& uniform_matrix)
	{
		glProgramUniformMatrix2fv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::mat2x3 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::mat2x3 const& uniform_matrix)
	{
		glProgramUniformMatrix2x3fv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::mat2x4 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::mat2x4 const& uniform_matrix)
	{
		glProgramUniformMatrix2x4fv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::mat3 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::mat3 const& uniform_matrix)
	{
		glProgramUniformMatrix3fv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::mat3x2 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::mat3x2 const& uniform_matrix)
	{
		glProgramUniformMatrix3x2fv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::mat3x4 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::mat3x4 const& uniform_matrix)
	{
		glProgramUniformMatrix3x4fv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::mat4 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::mat4 const& uniform_matrix)
	{
		glProgramUniformMatrix4fv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::mat4x2 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::mat4x2 const& uniform_matrix)
	{
		glProgramUniformMatrix4x2fv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name,, glm::mat4x3 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::mat4x3 const& uniform_matrix)
	{
		glProgramUniformMatrix4x3fv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::dmat2 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::dmat2 const& uniform_matrix)
	{
		glProgramUniformMatrix2dv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::dmat2x3 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::dmat2x3 const& uniform_matrix)
	{
		glProgramUniformMatrix2x3dv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::dmat2x4 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::dmat2x4 const& uniform_matrix)
	{
		glProgramUniformMatrix2x4dv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::dmat3 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::dmat3 const& uniform_matrix)
	{
		glProgramUniformMatrix3dv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::dmat3x2 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::dmat3x2 const& uniform_matrix)
	{
		glProgramUniformMatrix3x2dv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::dmat3x4 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::dmat3x4 const& uniform_matrix)
	{
		glProgramUniformMatrix3x4dv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::dmat4 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::dmat4 const& uniform_matrix)
	{
		glProgramUniformMatrix4dv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::dmat4x2 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::dmat4x2 const& uniform_matrix)
	{
		glProgramUniformMatrix4x2dv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <> inline void Programme::lierUniforme(std::string attribute_name, glm::dmat4x3 const& uniform_matrix)
	///
	/// Permet de lier une valeur à une uniforme des nuanceurs.
	///
	/// @param[in] attribute_name : le nom de l'uniforme
	/// @param[in]  uniform_matrix : la valeur de l'uniforme.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <>
	inline void Programme::lierUniforme(std::string attribute_name, glm::dmat4x3 const& uniform_matrix)
	{
		glProgramUniformMatrix4x3dv(handle_, mapUniforme[attribute_name], 1, false, glm::value_ptr(uniform_matrix));
	}

	namespace debug{
		////////////////////////////////////////////////////////////////////////
		///
		/// @fn void afficherDebugInfo(const Programme& programme)
		///
		/// Permet d'afficher une chaine de caractère représentant l'état du 
		/// programme.
		///
		/// @return Aucune.
		///
		////////////////////////////////////////////////////////////////////////
		void afficherDebugInfo(const Programme& programme)
		{
			std::cout << programme.serialiser();
			std::cout << ObtenirProgrammeLog(programme.obtenirHandle());
		}
	}
}

///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
