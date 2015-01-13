///////////////////////////////////////////////////////////////////////////////
/// @file ModeleStorage_CPU_Local.cpp
/// @author Martin Paradis
/// @date 2014-08-16
/// @version 1.0
///
/// @addtogroup modele Modele
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "GL/glew.h"

#include "ModeleStorage_CPU_Local.h"
#include "Modele3D.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "AideGL.h"

namespace modele{
	namespace opengl_storage{
		////////////////////////////////////////////////////////////////////////
		///
		/// @fn CPU_Local::CPU_Local(Modele3D const* modele)
		///
		/// Construit un storage local pour le dessin d'un modèle 3D.  Ne charge
		/// aucune donnée sur la carte graphique et utilise les commandes de 
		/// dessins (dépréciées) d'OpenGL pour dessiner le modèle 3D.
		///
		/// @param[in] modele : le modèle à dessiner.
		///
		/// @return Aucune.
		///
		////////////////////////////////////////////////////////////////////////
		CPU_Local::CPU_Local(Modele3D const* modele)
			: modele_{ modele }
		{}

		////////////////////////////////////////////////////////////////////////
		///
		/// @fn void CPU_Local::storageCharger()
		///
		/// Ne fait rien.
		///
		/// @return Aucune.
		///
		////////////////////////////////////////////////////////////////////////
		void CPU_Local::storageCharger() {}

		////////////////////////////////////////////////////////////////////////
		///
		/// @fn void CPU_Local::dessiner() const
		///
		/// Dessine le modèle 3D à partir de son noeud racine. 
		///
		/// @return Aucune.
		///
		////////////////////////////////////////////////////////////////////////
		void CPU_Local::dessiner() const
		{
			dessiner(modele_->obtenirNoeudRacine());
		}

		////////////////////////////////////////////////////////////////////////
		///
		/// @fn void CPU_Local::dessiner(modele::Noeud const& noeud) const
		///
		/// Dessine (de façon récursive) un noeud d'un modèle 3D en utilisant
		/// les commandes de rendu dépréciées d'OpenGL. 
		///
		/// @param[in] noeud : le noeud à dessiner
		///
		/// @return Aucune.
		///
		////////////////////////////////////////////////////////////////////////
		void CPU_Local::dessiner(modele::Noeud const& noeud) const
		{
			// Matrice de transformation
			glm::mat4x4 const& m{ noeud.obtenirTransformation() };

			/// Empiler la transformation courante
			glPushMatrix();
			glMultMatrixf(glm::value_ptr(m));

			/// Pour toutes les meshes contenus dans le noeud
			for (modele::Mesh const& mesh : noeud.obtenirMeshes())
			{
				// Appliquer le matériau pour le mesh courant
				appliquerMateriau(mesh.obtenirMateriau());

				bool possedeNormales{ mesh.possedeNormales() };
				bool possedeCouleurs{ mesh.possedeCouleurs() };
				bool possedeTexCoords{ mesh.possedeTexCoords() };
				bool possedeSommets{ mesh.possedeSommets() };

				possedeNormales ? glEnable(GL_LIGHTING) : glDisable(GL_LIGHTING);
				possedeCouleurs ? glEnable(GL_COLOR_MATERIAL) : glDisable(GL_COLOR_MATERIAL);

				/// Effectuer le rendu de toutes les faces (triangles)
				glBegin(GL_TRIANGLES);
				/// Effectuer le rendu de chaque face
				for (modele::Mesh::Face const& face : mesh.obtenirFaces())
				{
					/// Toutes les faces sont des triangles
					for (glm::length_t indexFace{ 0 }; indexFace < face.length(); ++indexFace)
					{
						int indexVertex{ face[indexFace] };	// get group index for current index

						/// Le mesh possède-t-il une couleur ?
						if (possedeCouleurs)
							glColor4fv(glm::value_ptr(mesh.obtenirCouleurs()[indexVertex]));
						/// Normales pour applications des textures
						if (possedeNormales)
							glNormal3fv(glm::value_ptr(mesh.obtenirNormales()[indexVertex]));
						/// texCoords
						if (possedeTexCoords)
							glTexCoord2f(mesh.obtenirTexCoords()[indexVertex].x, 1 - mesh.obtenirTexCoords()[indexVertex].y);
						/// sommets
						if (possedeSommets)
							glVertex3fv(glm::value_ptr(mesh.obtenirSommets()[indexVertex]));
					}
				}
				glEnd();

				/// Pour une raison ou une autre, il faut la désactiver après le dessin 
				/// si le modèle possède des couleurs de vertex.
				if (possedeCouleurs)
					glDisable(GL_COLOR_MATERIAL);
				if (possedeNormales)
					glDisable(GL_LIGHTING);

				glMatrixMode(GL_TEXTURE);
				glPopMatrix();
				glMatrixMode(GL_MODELVIEW);
			}

			// Rendu récursif des enfants
			for (modele::Noeud const& noeud : noeud.obtenirEnfants())
			{
				dessiner(noeud);
			}

			/// Pop de la transformation du noeud courant
			glPopMatrix();
		}

		////////////////////////////////////////////////////////////////////////
		///
		/// @fn void CPU_Local::storageRelacher()
		///
		/// Ne fait rien.
		///
		/// @return Aucune.
		///
		////////////////////////////////////////////////////////////////////////
		void CPU_Local::storageRelacher() {}

		////////////////////////////////////////////////////////////////////////
		///
		/// @fn void CPU_Local::appliquerMateriau(modele::Materiau const& materiau) const
		///
		/// Assigne un matériau OpenGL selon la méthode dépréciée d'illumination
		/// d'OpenGL
		///
		/// @param[in] materiau : le materiau à assigner
		///
		/// @return Aucune.
		///
		////////////////////////////////////////////////////////////////////////
		void CPU_Local::appliquerMateriau(modele::Materiau const& materiau) const
		{
			/// Assigner la texture
			glMatrixMode(GL_TEXTURE);
			glPushMatrix();

			/// Vérifier si texture existe
			if (modele_->possedeTexture(materiau.nomTexture_)) {
				// Activer le texturage OpenGL et lier la texture appropriée
				glEnable(GL_TEXTURE_2D);
				glScalef(1.0, -1.0, 1.0);
				glBindTexture(GL_TEXTURE_2D, modele_->obtenirTextureHandle(materiau.nomTexture_));
			}
			else {
				// Désactiver le texturage OpenGL puisque cet objet n'a aucune texture
				glBindTexture(GL_TEXTURE_2D, 0);
				glDisable(GL_TEXTURE_2D);
			}

			/// Assigner la matériau
			glMatrixMode(GL_MODELVIEW);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(materiau.diffuse_));
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(materiau.speculaire_));
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(materiau.ambiant_));
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(materiau.emission_));
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, materiau.shininess_ * materiau.shininessStrength_);

			glPolygonMode(
				GL_FRONT_AND_BACK,
				materiau.filDeFer_ ? GL_LINE : GL_FILL);

			materiau.afficherDeuxCotes_ ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);

		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////