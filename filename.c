
#include "includes.h"

char pTxtRecovery[100000];
char pTxtAtTranslation[10000][1000];

#define FILENAME_SAVE_SUB "filesave.txt"


int Filename_ChoiceUser(void)
{
  char pInput[2] = {};
  while(1){
    Filename_RecoveryInputUser(pInput, "q ou Q pour quitter, entrée pour continuer.\n");
    
    if( pInput[0] == 'q' || pInput[0] == 'Q')
      return 1;
    else if(pInput[0] != '\n')
      return 0;
  }
}

void Filename_CleanStdin(void)
{
  char cc;
  do
  {
    // Note : si on met stdin la console attendra toujour que l'utilisateur tape entrée, que ce soit
		// fgetc ou fgets pour valider.
    // c = fgetc(stdin); 
		
		cc = fgetc(stdin);
  }while(cc != '\n' && cc !=EOF);
}
		
void Filename_WaitingTxt(void)
{
	char pInput[2] = {};
	int i = 0;
	
	while(1)
	{
		printf("\nAttente de la traduction. Tapez entrée pour continuer.\n");
		if(fgets(pInput, 2, stdin) != NULL)
		{
			char *LF = strchr(pInput, '\n');
			if(LF != NULL)
			{
				*LF = '\0';
				break;
			}
			else
			{
				Filename_CleanStdin();
			}
		}
		else
		{
			printf("Impossible de récupéré la saisie utilisateur.\n");
		}
	}
}

char *Filename_MsgError(char *pTxtError)
{
	return pTxtError;
}

void Filename_VerifCara(char *tab)
{
	int nExit = 1;
	int i = 0;
	while(nExit) 
	{
		if(tab[i] == 10)
			printf("%d", tab[i]);
		else
		{
			printf("%c", tab[i]);
		}
		if(tab[i] == 0)
			nExit = 0;
		i++;
	}
	printf("\n");
}

void Filename_TreatmentVostATOvostFR(FILE *pFile)
{
	char cc;
	int nCount = 0;
	int i = 0, j = 0, k = 0;

	while(pTxtAtTranslation[i][0] != '\0')
	{
		while((cc = pTxtAtTranslation[i][j]) != '\0')
		{
			if(cc == ',' && nCount < 3)
			{
				nCount++;
			}
			else
			{
				nCount = 0;
			}

			if(nCount == 2)
			{
				// On met tout à zéro pour éviter qu'il reste des caractères précédent.
				// j+1 pour éviter d'écraser la 2e virgule.
				for(int jj = j+1; pTxtAtTranslation[i][jj] != '\0'; jj++)
				{
					pTxtAtTranslation[i][jj] = '\0';
				}
				do
				{
					// ++i pour ne pas écraser la 2e virgule.
					pTxtAtTranslation[i][++j] = pTxtRecovery[k++]; 

				}while(pTxtRecovery[k] != 10); 

				// Remplace le 10.
				pTxtRecovery[k] = '\n';
				nCount = 0;
				// Pour passé à la case qui est après 10. 
				k++;
				break;
			}
			j++;
		}
		j=0;
		i++;
	}

	// On revient au début.
	rewind(pFile);
	// Pour faire une page vierge.
	fwrite(NULL, 0, 0, pFile);
	
	for(int i = 0; pTxtAtTranslation[i][0] != '\0'; i++)
	{
		fwrite(pTxtAtTranslation[i], strlen(pTxtAtTranslation[i]), 1, pFile);
		fwrite("\n", strlen("\n"), 1, pFile);
	}
}

void Filename_RecoveryFileSrc(FILE *pFile)
{
	char cc;
	int i=0, j=0;

	for(int i = 0; i < 10000; i++)
		memset(pTxtAtTranslation[i], '\0', sizeof(pTxtAtTranslation[i]));
	while((cc = fgetc(pFile)) != EOF)
	{
		pTxtAtTranslation[i][j++] = cc;
		if(cc == 10)
		{
			pTxtAtTranslation[i][j]='\0';
			i++; j=0;
		}
	}
}

void Filename_SaveTxt(char *pTxt, FILE *pFile)
{
	fwrite(pTxt, strlen(pTxt), 1, pFile);
}

void Filename_TreatmentSubVostFR(FILE *pFile)
{
	char cc;
	int i = 0;
	while((cc = fgetc(pFile)) != EOF)
	{
			if(cc == '#' && fgetc(pFile) == '#')
				{
					pTxtRecovery[i++] = '\\';
					pTxtRecovery[i++] = 'N';
				}
			else
				pTxtRecovery[i++] = cc;
	}
}

void Filename_RecoverySubVostA(FILE *pFile)
{	
	Filename_RecoveryFileSrc(pFile);
	char cc;
	int nCount = 0;
	int i = 0, j = 0, k = 0;

	while(pTxtAtTranslation[i][0] != '\0')
	{ 
		while((cc = pTxtAtTranslation[i][j]) != '\0')
		{
			if(cc == ',' && nCount < 3)
			{
				nCount++;
			}
			else
			{
				nCount = 0;
			}

			if(nCount == 2)
			{
				do
				{
					cc = pTxtAtTranslation[i][++j];
					if(cc == '\\' && pTxtAtTranslation[i][j+1] == 'N')
					{
						pTxtRecovery[k] = '#';
						pTxtRecovery[++k] = '#';
						// j++ pour ne pas traiter le 'N' car remplacé par le dièse ci-dessus.
						pTxtAtTranslation[i][j]= '\0'; // On efface les sous-titres.
						pTxtAtTranslation[i][j+1]= '\0';
						j++; 
					}
					else
					{
						if(cc != '\0')
						{
							pTxtRecovery[k] = cc;
							pTxtAtTranslation[i][j]= '\0'; // On efface les sous-titres.
						}
					}
					k++;
				}while(cc != '\0'); 
				nCount = 0;
				k--; // On recule d'une case pour écraser le '\0'.
				break;
			}
			j++;
		}
		i++; j=0;
	}

	// // On sauvegarde les sous-titres à traduire dans un fichier texte.
	FILE * pFilesave = fopen(FILENAME_SAVE_SUB, "w");
	Filename_SaveTxt(pTxtRecovery, pFilesave);
	fclose(pFilesave);
	memset(pTxtRecovery, 0, sizeof(pTxtRecovery));
}



// fgets ajoute en plus de la chaîne '\0'.
// On met -1 à la taille de la chaîne car comme on est dans stdin la touche entré ('\n') est ajouté
// à la chaîne donc on le supprime. Ex. : salut puis entrée donne : salut\n, strlen comptera 5 + 1
// (\n) caractère.
char * Filename_RecoveryInputUser(char *pArray, char *pMsg)
{
	printf("%s", pMsg);
		
	if(fgets(pArray, PATH_MAX+1, stdin)  != NULL)
	{
		char * LF = strchr(pArray, '\n');
		if(LF != NULL)
			*LF = '\0';
		else
			Filename_CleanStdin();
	}
	return pArray;
}

void Filename_CloseFile(FILE *pFile)
{				
	fclose(pFile);
}

void Filename_TreatmentTranslationSub(void)
{
		FILE *pFile = fopen(FILENAME_SAVE_SUB, "r");
  	Filename_TreatmentSubVostFR(pFile);
		fclose(pFile);
}

FILE *Filename_OpenFile(char *pMode, char *pErrorMsg)
{
	char pFilename[PATH_MAX+1]; // Buffer pour récupérer la saisie utilisateur.  
	FILE *pFile = NULL;

  char *pMsg = "Saisir le nom du fichier a traduire.\n\
Un fichier texte du nom de filesave.txt sera crée ; \
il contiendra le texte à traduire.\n";
  
	while(1)
	{
		pFile = fopen(strcat(Filename_RecoveryInputUser(pFilename, pMsg),".ass"), pMode); // fopen n'admet pas les '\n'.
		if(pFile != NULL) break;

		printf("Enter a valid file name.\n");
		if (pErrorMsg != NULL) 
			printf("%s\n", pErrorMsg);
	}
	return pFile;
}


