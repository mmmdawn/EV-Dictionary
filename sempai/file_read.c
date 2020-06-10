void file_read(FILE *f)
{
    char word[20],mean[5000],*p1,*p2;
    int mem;
    while(1)
    {
        fscanf(f,"%s ",word);
        if(feof(f)) break;
        mem=strlen(word)+1;
        p1=(char *) malloc(mem*sizeof(char));
        strcpy(p1,word);
        while(1)
        {
            if(fgetc(f)=='@')
            {
                fseek(f,-1,SEEK_CUR);
                break;
            }
            else fseek(f,-1,SEEK_CUR);
            fscanf(f,"%s ",word);
            mem+=strlen(word)+1;
            p1=(char *) realloc(p1,mem*sizeof(char));
            strcat(p1," ");
            strcat(p1,word);
        }
        fgets(mean,5000,f);
        p2=(char *) malloc((strlen(mean)+1)*sizeof(char));
        strcpy(p2,mean);
        printf("%s %s\n",p1,p2);
    }
}
