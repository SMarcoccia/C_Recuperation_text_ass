
#include "includes.h"

// ATTENTION : si fgetc après fputc efface le caractère lu.
// Si on rajoute fseek(fichier, -1, SEEK_CUR); entre les 2, plus de problème.
// ATTENTION : si fgetc avant fputc, fputc ne remplace pas le caractère.
// Si on rajoute fseek(fichier, -1, SEEK_CUR); entre les 2, plus de problème.
// fseek risuque de conflits (à vérifier).
// Obtez pour un traitement dans la ram.

int main(int argc, char const **argv)
{
    freopen("CON", "w", stdout);
		// Récupère les sub anglais que l'on met dans un fichier .txt.
		// Note : après avoir traduit le fichier, à la fin de la dernière phrase sauté une
		//        ligne. 
    FILE *pFile;
    while(1){
      pFile = Filename_OpenFile("r+", NULL);
      Filename_RecoverySubVostA(pFile);

      // En attente du copiage de la traduction dans le filesave.txt.
      Filename_WaitingTxt(); 
      Filename_TreatmentTranslationSub();

      // On replace la traduction dans le fichier.
      Filename_TreatmentVostATOvostFR(pFile);
      Filename_CloseFile(pFile);

      if(Filename_ChoiceUser())
        break;
    }

    return 0;
}
