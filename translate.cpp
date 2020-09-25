#include <cstdio>
#include <cstdlib>
const char *infile = "input.txt";
const char *outfile = "output.bf";

int main(){
  FILE *infp;
  FILE *outfp;
  int ch;

  if((infp = fopen(infile,"r")) == NULL){
    printf("Error : \"input.txt\" does not exist\n");
    exit(1);
  }
  if((outfp = fopen(outfile,"a")) == NULL){
    printf("Error : \"output.bf\"\n");
    exit(1);
  }

  fprintf(outfp,"++++++++[");
  for(int i=1; i<16; i++){
    fprintf(outfp,">");
    for(int j=1; j<=i; j++){
      fprintf(outfp,"+");
    }
  }
  fprintf(outfp,"<<<<<<<<<<<<<<<-");
  fprintf(outfp,"]");

  int now = 0;
  int next;
  while(( ch = fgetc(infp)) != EOF){
    int ldist = ch-ch/8*8;
    int rdist = (ch/8+1)*8-ch;
    
    if(ldist <= rdist){
      next = ch/8*8;
      if(next < now){
        int dif = (now-next)/8;
        for(int i=1; i<=dif; i++) fprintf(outfp,"<");
      }
      else if(next > now){
        int dif = (next-now)/8;
        for(int i=1; i<=dif; i++) fprintf(outfp,">");   
      }
      for(int i=1; i<=ldist; i++) fprintf(outfp,"+"); 
      fprintf(outfp,".");
      for(int i=1; i<=ldist; i++) fprintf(outfp,"-");
    }else{
      next = (ch/8+1)*8;
      if(next < now){
        int dif = (now-next)/8;
        for(int i=1; i<=dif; i++) fprintf(outfp,"<");
      }
      else if(next > now){
        int dif = (next-now)/8;
        for(int i=1; i<=dif; i++) fprintf(outfp,">");
      }
      for(int i=1; i<=rdist; i++) fprintf(outfp,"-");
      fprintf(outfp,".");
      for(int i=1; i<=rdist; i++) fprintf(outfp,"+");
    }
    now = next;
  }
  
  fclose(outfp);
  fclose(infp);
  return 0;
}