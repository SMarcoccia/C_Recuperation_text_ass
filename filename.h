
// Continuer ou quitter.
int Filename_ChoiceUser(void);
// Vide le buffer clavier si la taille du buffer à été dépassé.
void Filename_CleanStdin(void);
// Attente de la traduction qui doit être collé dans le fichier texte.
void Filename_WaitingTxt(void);
// Message d'erreur personnalisé si le fichier ne s'ouvre pas.
char * Filename_MsgError(char *pTxtError);
// On récupère le fichier source que l'on met dans un tableau.
// Facilite le traitement du texte (évite les conflits entre fgetc et fputc).
void Filename_RecoveryFileSrc(FILE *pFile);
// Verifie les phrases récupéré dans le fichier texte traduit.
void Filename_VerifCara(char *tab);
// Remplace le texte anglais en français.
void Filename_TreatmentVostATOvostFR(FILE *pFile);
// On met dans un tableau, le texte traduit en français.
// On fait un traitement sur le fichier pour remettre les \N.
void Filename_TreatmentSubVostFR(FILE *pFile);
// Sauvegarde du texte à traduire dans un fichier par défaut.
// char *pTxt : ce qui sera mis dans le texte.
void Filename_SaveTxt(char *pTxt, FILE *pFile);
// Récupération des sous-titres VOSTA.
// On remplace le \N par 2 dièses pour éviter les erreurs de traductions du logiciel.
void Filename_RecoverySubVostA(FILE *pFile);
// Récupération de la saisie utilisateur.
// Paramètre : envoi un tableau pour récupérer la saisie.
char *Filename_RecoveryInputUser(char *pArray, char *pMsg);
// Fermeture du fichier ass.
void Filename_CloseFile(FILE *pFile);
// Traitement (remise des \N) des sous-titres traduits.
void Filename_TreatmentTranslationSub(void);
// Ouverture d'un fichier.
FILE *Filename_OpenFile(char *pMode, char *pErrorMsg);
