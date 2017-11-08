#include <stdio.h>
#include <string.h>   /* for all the new-fangled string functions */
#include <stdlib.h>     /* malloc, free, rand */

const int Fsize=50;
int no_edges;
int no_nodes;
int i;
const int cases=15;
// Parse a formula and return appropiate value
int parse(char *g)
{/* return 1 if atomic, 2 if  neg, 3 if binary, 4 if exists, 5 if for all, ow 0*/
int rect=0; // counters for the square brackets and parenthesis; check if equal number of right and left.
int rectright=0;
int squarel=0;
int squareright=0;
int binaryconn=0;
int position,a =0,numbeer=0;
int i,b,c,d,e;
int ncount=0;
int startfromone=0,start=0,starting=0,final=0;
for(position=0; g[position] != '\0'; ++position){
    if (g[position]== '[') {
      b=position+1;
      ++rect;
      if(g[b] != 'x')
        ++startfromone;
      if(g[b] != 'y')
        ++startfromone;
      if (g[b] != 'z')
        ++startfromone;
      if(startfromone != 2*rect)
        return 0;
  }
    if(g[position] == ']') {
      c=position-1;
      ++rectright;
      if(g[c] != 'x')
        ++start;
      if(g[c] != 'y')
        ++start;
      if (g[c] != 'z')
        ++start;
      if(start != 2*rectright)
        return 0;
  }
    if(g[position] == '(')
      ++squarel;
    if(g[position] == ')')
      ++squareright;
    if(g[position] == 'v' || g[position] == '^' || g[position] == '>')
      ++binaryconn;
    if(g[position] == 'X'){
      i=position+1;
      if(g[i] != '[')
        return 0;
      }
    if(g[position] == 'A') {
      d=position+1;
      a++;
      if(g[d] != 'x' )
        ++starting;
      if(g[d] != 'y')
        starting++;
      if(g[d] != 'z')
        starting++;
      if(2*a != starting)
        return 0;

      }
    if (g[position] == 'E') {
      e=position+1;
      numbeer++;
      if(g[e] != 'x')
        ++final;
      if(g[e] != 'y')
        ++final;
      if(g[e] != 'z')
        ++final;
      if(2*numbeer != final)
        return 0;
    }
}
  if(rect != rectright || squareright != squarel || (squarel+squareright) != 2*binaryconn)
      return 0;

      switch(g[0]) {

        case 'p':
          if(g[1]== '\0') {
            return 1; }
            else {
              break;
            }
        case 'q':
        if(g[1]== '\0') {
          return 1; }
          else {
            break;
          }
        case 'r':
        if(g[1]== '\0') {
          return 1; }
          else {
            break;
          }
        case 'X':
          if(g[1] == '[' && g[4] == ']' && g[5] == '\0')
            return 1;
          else
            break;
      case '-':
        i=0;
        while(g[i]!='\0') {
          if(g[i] == '-' && g[i+1] =='-') {
            ncount=ncount+1;
          }
          else if(g[i] == '-' && g[i+1] =='\0'){
            ncount=ncount+1;
            break;
          }
          else if(g[i] == '-' || g[i+1] =='p' || g[i+1] =='q'|| g[i+1] =='('){
            ncount=ncount+1;
            break;
          }
          else
            break;
          i++;
        }
        if(ncount % 2==0)
          return 1;
        else if(ncount % 2!=0)
          return 2;
        else
          break;
       case '(':
        if(binaryconn < 1)
          return 0;
        else
          return 3;
       case 'E':
        if(g[2] == 'X' || g[2] == 'E')
          return 4;
        else if(g[2] == '(' || g[2] == 'A')
          return 4;
        else
          return 0;
       case 'A':
        if(g[2] == 'X'|| g[2] == 'A')
          return 5;
        else if(g[2] == '(' || g[2] == 'E')
          return 5;
        else
          return 0;
      default:
        break;
    }
return 0;
}

int main()
{
  char *name=malloc(Fsize);
  FILE *fp, *fpout, *fopen();

  /* reads from input.txt, writes to output.txt*/
 if ((  fp=fopen("input.txt","r"))==NULL){printf("Error opening file");exit(1);}
  if ((  fpout=fopen("output.txt","w"))==NULL){printf("Error opening file");exit(1);}

  int j;
  for(j=0;j<cases;j++)
    {
      fscanf(fp, "%s",name);//read number of nodes, number of edges

      int p=parse(name);
      switch(p)
      	{case 0:fprintf(fpout,"%s is not a formula. \n ", name);break;
      	case 1: fprintf(fpout,"%s is a Proposition. \n ",name);break;
      	case 2: fprintf(fpout,"%s is a negated formula. \n ",name);break;
      	case 3: fprintf(fpout,"%s is a binary formula. \n ", name);break;
      	default: fprintf(fpout,"%s is not a formula. \n ",name);break;
      	}


    }

  fclose(fp);
  fclose(fpout);
  free(name);
  return(0);
}