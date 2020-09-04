void shell_cat(int param, char** args) {
  FILE *file;
  for(int cnt = 1; cnt < param; cnt++) 
  {
    if((file = fopen(args[cnt], "r")) == NULL) 
    {
      fprintf(stdout, "%s: %s : %s\n", args[0], args[cnt], strerror(errno));
      continue;
    }
    struct stat filestat;
    stat(args[cnt], &filestat);
    if(!S_ISREG(filestat.st_mode))
    {
      fprintf(stdout,"Parameter is not a file");
    }
    else
    {
      int chr;
      while((chr = getc(file)) != EOF)
      {
      fprintf(stdout, "%c", chr);
      }
      fprintf(stdout,"\n");
    }
    fclose(file);
  }
}
