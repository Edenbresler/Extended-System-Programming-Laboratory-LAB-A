
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
int main(int argc, char **argv){

    FILE* infile = stdin;
    FILE* outfile = stdout;

    int debug_mode =1;
    int encode_mode = 0;
    char* key_location= NULL;
    int first_index_key =0;
    int sec_index_key =2 ;
    int curr_char_to_encode;
    for (int i = 1; i < argc; i++)
    {
        if (debug_mode ==1){
            fprintf(stderr, "%s\n",argv[i]);
            
        }
        
        if((argv[i][0]=='+') && (argv[i][1]=='D') ){
            debug_mode =1;
        }
        if((argv[i][0]=='-') && (argv[i][1]=='D')){
            debug_mode =-1;
        }
        if((argv[i][0] == '+') && (argv[i][1]=='E') ){
            encode_mode=1;
            key_location =&(argv[i][2]);
            first_index_key = i;
            
        }
        if((argv[i][0] == '-')  && (argv[i][1]=='E') ){
            encode_mode=-1;
            key_location =&(argv[i][2]);
            first_index_key = i;
            
        }
        if((argv[i][0] == '-')  && (argv[i][1]=='I') ){
            fclose(infile);
            infile = fopen(&(argv[i][2]),"r");
            if(infile == NULL){
            fprintf(stderr, "Error opening input file\n");
                if(outfile != stdout)
                    fclose(outfile);
                exit(1);
                
            }            
        }
        if((argv[i][0] == '-')  && (argv[i][1]=='O') ){
            fclose(outfile);
            outfile = fopen(&(argv[i][2]),"w");
            if(outfile == NULL){
                fprintf(stderr,"Failed to open outfile\n");
                if(infile != stdin)
                    fclose(infile);
                exit(1);
                } 
        }

    
 
    }
    if (encode_mode !=0){
        curr_char_to_encode = fgetc(infile);
        while (curr_char_to_encode != EOF) {
            key_location = &argv[first_index_key][sec_index_key];

            

            if (*key_location == '\0') {
                sec_index_key = 2;  // Reset the index if at the end of the key
                key_location = &argv[first_index_key][sec_index_key];
                
            }
            int the_difference = *key_location - '0';
            if(curr_char_to_encode >= 'A' && curr_char_to_encode <= 'Z'){
                if(encode_mode ==1){
                    fputc((curr_char_to_encode - 'A' + the_difference) % 26 + 'A', outfile);

                }
                else
                {
                    fputc((curr_char_to_encode-'A'-the_difference+26)%26+'A',outfile);
                }
                
            }
            else if(curr_char_to_encode >= '0' && curr_char_to_encode <= '9'){
                if(encode_mode ==1){
                    fputc((curr_char_to_encode-'0'+the_difference)%10+'0',outfile);
                }
                else
                {
                    fputc((curr_char_to_encode-'0'-the_difference+10)%10+'0',outfile);
                }
            }

            else{
                fputc(curr_char_to_encode,outfile);
            }
            
            ++sec_index_key;
            curr_char_to_encode = fgetc(infile);
            
        


        }
 

    }

            fclose(infile);
            fclose(outfile);


    return 0;
}