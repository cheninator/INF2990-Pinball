///////////////////////////////////////////////////////////////////////////////
/// @file ModeleStorage_Liste.cpp
/// @author Martin Paradis
/// @date 2014-08-16
/// @version 1.0
///
/// @addtogroup modele Modele
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "GL/glew.h"

#include "ModeleStorage_Liste.h"
#include "ModeleStorage_CPU_Local.h"
#include "Modele3D.h"
#include "AideGL.h"
#include "Utilitaire.h"

namespace modele{
	namespace opengl_storage{
		////////////////////////////////////////////////////////////////////////
		///
		/// @fn OpenGL_Liste::OpenGL_Liste(modele::Modele3D const* modele)
		///
		/// Assigne le modèle 3D.
		///
		/// @param[in] modele : le modele 3D à dessiner.
		///
		/// @return Aucune.
		///
		////////////////////////////////////////////////////////////////////////
		OpenGL_Liste::OpenGL_Liste(modele::Modele3D const* modele)
			: modele_{ modele }
		{}

		////////////////////////////////////////////////////////////////////////
		///
		/// @fn OpenGL_Liste::~OpenGL_Liste()
		///
		/// Destructeur, relâche la liste OpenGL.
		///
		/// @return Aucune.
		///
		////////////////////////////////////////////////////////////////////////
		OpenGL_Liste::~OpenGL_Liste()
		{
			storageRelacher();
		}

		////////////////////////////////////////////////////////////////////////
		///
		/// @fn void OpenGL_Liste::storageCharger()
		///
		/// Charge les commandes de dessin du modèle 3D dans une liste OpenGL en
		/// utilisant opengl_storage::CPU_Local pour effectuer le dessin.
		///
		/// @return Aucune.
		///
		////////////////////////////////////////////////////////////////////////
		void OpenGL_Liste::storageCharger()
		{
			opengl_storage::CPU_Local primitives{ modele_ };
			handle_ = glGenLists(1);
			if (!identifiantEstValide())
				return;

			glNewList(handle_, GL_COMPILE);
			primitives.dessiner();
			glEndList();
		}

		////////////////////////////////////////////////////////////////////////
		///
		/// @fn void OpenGL_Liste::dessiner() const
		///
		/// Appelle la liste OpenGL pour effectuer le dessin du modèle 3D.
		///
		/// @return Aucune.
		///
		////////////////////////////////////////////////////////////////////////
		void OpenGL_Liste::dessiner() const
		{
			if (identifiantEstValide())
				glCallList(handle_);
		}

		////////////////////////////////////////////////////////////////////////
		///
		/// @fn void OpenGL_Liste::storageRelacher()
		///
		/// Relâche la liste OpenGL.
		///
		/// @return Aucune.
		///
		////////////////////////////////////////////////////////////////////////
		void OpenGL_Liste::storageRelacher()
		{
			if (identifiantEstValide())
				glDeleteLists(handle_, 1);
			handle_ = 0;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////