#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

/******************************************Structure****************************************************/

typedef struct num_struct{
	char name[30];
	int valid;
	struct num_struct* next;
} num_struct;

typedef struct gate_struct{
	char name[30];
	char input1[15];
	char input2[15];
	char output[15];
	struct gate_struct* next;
} gate_struct;

// creat New num_structure
num_struct* create_num_struct(num_struct* temphead, char* name){
    if(temphead==NULL){
        temphead=malloc(sizeof(num_struct));
        strcpy(temphead->name,name);
        temphead->next=NULL;
        return temphead;
    }
    num_struct* pt=temphead;
    while(pt->next!=NULL) {
        pt=pt->next;
    }
    num_struct* new=malloc(sizeof(num_struct));
    strcpy(new->name,name);
    new->next=NULL;
    pt->next=new;
    return temphead;
}

int get_nth_bit_from_left(int num, int shift) {
	return (num >> shift) & 1;
}

/************************ ALL Gate functions ****************************************************/
int not_gate(int ip){
    if (ip==1) {
        return 0;
    }else if(ip==0) {
        return 1;
    }
    return 2;
}

int and_gate(int ip1,int ip2) {
    if(ip1==1 && ip2==1){
        return 1;
    }
	return 0;
}

int or_gate(int ip1,int ip2) {
    if(ip1==1 || ip2==1){
        return 1;
    }
    return 0;
}

int nand_gate(int ip1,int ip2) {
    if(ip1==0 && ip2==0){
        return 1;
    }
    return 0;
}

int nor_gate(int ip1,int ip2) {
    if(ip1==1 || ip2==1) {
        return 0;
    }
    return 1;
}

int xor_gate(int ip1,int ip2){
    if (ip1==1 && ip2==0) {
        return 1;
    }else if (ip1==0 && ip2==1) {
        return 1;
    }
    return 0;
}

// create Gate LinkedList
gate_struct* create_gate(gate_struct* temphead,char* name,char* input1,char* input2,char* output) {
    if(temphead==NULL){
        temphead=malloc(sizeof(gate_struct));
        strcpy(temphead->name,name);
        strcpy(temphead->input1,input1);
        strcpy(temphead->input2,input2);
        strcpy(temphead->output,output);
        temphead->next=NULL;
        return temphead;
    }
    gate_struct* pt=temphead;
    while(pt->next!=NULL){
        pt=pt->next;
    }
    gate_struct* new= malloc(sizeof(gate_struct));
    strcpy(new->name,name);
    strcpy(new->input1,input1);
    strcpy(new->input2,input2);
    strcpy(new->output,output);
    new->next=NULL;
    pt->next=new;
    return temphead;
}
/*
gate_struct_decoder* create_gate_decoder(gate_struct_decoder* temphead,char* name,char* input1,char* input2,char* input3) {
	if(temphead==NULL){
        temphead=malloc(sizeof(gate_struct_decoder));
        strcpy(temphead->name,name);
        strcpy(temphead->input1,input1);
        strcpy(temphead->input2,input2);
		strcpy(temphead->input3,input3);
		//temphead->output = output;
		for(testCount = 0; testCount < 8; testCount++){
			strcpy(temphead->output[testCount],multiEx[testCount]);
		}

        temphead->next=NULL;
        return temphead;
    }
    gate_struct_decoder* pt=temphead;
    while(pt->next!=NULL){
        pt=pt->next;
    }
    gate_struct_decoder* new= malloc(sizeof(gate_struct_decoder));
    strcpy(new->name,name);
    strcpy(new->input1,input1);
    strcpy(new->input2,input2);
	strcpy(new->input3,input3);
    for(testCount = 0; testCount < 8; testCount++){
		strcpy(temphead->output[testCount],multiEx[testCount]);
	}
    new->next=NULL;
    pt->next=new;

    return temphead;
}
*/

// Find Input LinkedList name and return the value
int find_input_name(char* name, num_struct* head)
{
	if (*name=='1') {
		return 1;
	} else if (*name=='0') {
		return 0;
	}

	num_struct* pt = head;
	while(pt!=NULL)
	{
		//printf("name:%s | pt->name:%s |\n", name, pt->name);
		if(strcmp(pt->name,name)==0){
			return pt->valid;
		}
		pt=pt->next;
	}
	return 2;
}

// Find Output LinkedList name and return the bl(1:yes 2:not)
int find_output_name(char* name,int n, num_struct* head){
	num_struct* pt=head;
	while(pt!=NULL){
		//printf("name:%s | pt->name:%s |\n", name, pt->name);
		if(strcmp(pt->name, name)==0){
			pt->valid = n;
			return 1;
		}
        pt=pt->next;
	}
    return 2;
}

/*
void free_num_struct(struct num_struct* head) {
  struct num_struct* temp;
  while (head != NULL) {
    temp = head;
    head = head -> next;
    free(temp);
   }
}
*/
void free_num_struct(struct num_struct** head)
{
    struct num_struct* prev = *head;
    while (*head) {
        *head = (*head)->next;
        free(prev);
        prev = *head;
    }
}
void print_output(struct num_struct** head)
{
    struct num_struct* prev;
    while (*head) {
        prev = *head;
        //printf("name:%s | %d ", prev->name, prev->valid);
        printf("%d\t", prev->valid);
        *head = (*head)->next;
    }
	printf("\n");
}

/*
void free_gate_struct(struct gate_struct* head) {
  struct gate_struct* temp;
  while (head != NULL) {
    temp = head;
    head = head -> next;
    free(temp);
   }
}
*/
void free_gate_struct(struct gate_struct** head)
{
    struct gate_struct* prev = *head;
    while (*head) {
        *head = (*head)->next;
        free(prev);
        prev = *head;
    }
}

void free_char_ptr(char **x) {
  free(*x);
  *x = NULL;
}

/*
void free_int_ptr(int **x) {
  free(*x);
  *x = NULL;
}

void free_int_ptr2(int **x, int cnt) {
  for (int i=(cnt-1); i>=0; i--){
  	free(x[i]);
  	x[i] = NULL;
  }
}
*/

int is_CAPS(char cc)
{
	if (cc >= 'A' && cc <= 'Z') {
		return 0;
	}
	return 1;
}

/******************************************Main function****************************************************/
int main(int argc, char** argv) {

	int input,output,num1,num2,num3,bl;
	int i,j;
	char* name=malloc(20*sizeof(char));
	char* curr_oper=malloc(20*sizeof(char));
	char* name1=malloc(20*sizeof(char));
	char* name2=malloc(20*sizeof(char));
	char* name3=malloc(20*sizeof(char));
	num_struct* in_head=NULL;
	num_struct* out_head=NULL;
	int total_oper=0;

	FILE* in_file = fopen(argv[1], "r");	// read only mode
	if (in_file == NULL)  {
        printf("Could not open file.\n");
		return 1;
	}

	// reading 1st line - Total Operations
    fscanf(in_file, "%d", &total_oper);
    fscanf(in_file,"\n");   // end-of line
    if (total_oper<3){
        return 1;
    }
    //printf("total_oper: %d\n",total_oper);

    /*read gate and store in gate LL*/
    gate_struct* gate = NULL;

  // Getting All Operations

	for (int op=0; op<total_oper; op++)
	{
    	fscanf(in_file,"%s",curr_oper);
       	//printf("curr_oper: %s\n", curr_oper);

		if(strcmp(curr_oper,"INPUTVAR")==0) {
			// read num of input and store in in_head LinkedList
			fscanf(in_file,"%d",&input);
			//printf("input is %d\n", input);

			for (i=0; i<input; i++) {
				fscanf(in_file,"%s",name);
				//printf("name is %s\n",name);
				in_head = create_num_struct(in_head, name);
			}
			fscanf(in_file,"\n");   // end-of line
    	}
		else if(strcmp(curr_oper,"OUTPUTVAR")==0) {
			// read num of output and store in out_head LinkedList
			fscanf(in_file,"%d",&output);
			//printf("output is %d\n",output);

			for (i=0; i<output; i++) {
				fscanf(in_file,"%s",name);
				//printf("name is %s\n",name);
				out_head = create_num_struct(out_head,name);
			}
			fscanf(in_file,"\n");   // end-of line
    	}
        else if(strcmp(curr_oper,"NOT")==0) {
            fscanf(in_file,"%s %s\n",name1,name2);
            gate = create_gate(gate,curr_oper,name1,name2,name2);
        }
        else if(strcmp(curr_oper,"AND")==0){
            fscanf(in_file,"%s %s %s\n",name1,name2,name3);
            //printf("name1:%s | name2:%s | name3:%s \n", name1, name2, name3);
            gate = create_gate(gate,curr_oper,name1,name2,name3);
        }
        else if(strcmp(curr_oper,"OR")==0){
            fscanf(in_file,"%s %s %s\n",name1,name2,name3);
            gate = create_gate(gate,curr_oper,name1,name2,name3);
        }
        else if(strcmp(curr_oper,"NAND")==0){
            fscanf(in_file,"%s %s %s\n",name1,name2,name3);
            gate=create_gate(gate,curr_oper,name1,name2,name3);
        }
        else if(strcmp(curr_oper,"NOR")==0){
            fscanf(in_file,"%s %s %s\n",name1,name2,name3);
            gate=create_gate(gate,curr_oper,name1,name2,name3);
        }
        else if(strcmp(curr_oper,"XOR")==0){
            fscanf(in_file,"%s %s %s\n",name1,name2,name3);
            gate=create_gate(gate,curr_oper,name1,name2,name3);
        }
        else if(strcmp(curr_oper,"DECODER")==0){
		/*
            //gate = create_gate(gate,curr_oper,name1,name2,name3,multi);
            fscanf(in_file,"%d", &input);
			fscanf(in_file,"%s %s %s\n",name1,name2,name3);
			for(i = 0; i < 8; i ++) {
				fscanf(in_file, "%s", multiEx[i]);
			}
            gate_decoder = create_gate_decoder(gate_decoder,curr_oper,name1,name2,name3);
        */
        }
        else if(strcmp(curr_oper,"MULTIPLEXER")==0){
			//mux logic goes here...
        }
    }

	//De-allocate Memory
	free_char_ptr(&name);
  	free_char_ptr(&curr_oper);
	free_char_ptr(&name1);
	free_char_ptr(&name2);
	free_char_ptr(&name3);

    num_struct* temphead = NULL;

  // Getting All Inputs now

	int test_num=0;
	while(fscanf(in_file, "%d\n", &test_num)==1)
	{
		//printf("test_num:%d\n",test_num);

		//storing input bit-value to input-head
    	num_struct* pt = in_head;
     	for (j=0; j<input; j++) {
    		pt->valid = (int) get_nth_bit_from_left(test_num, (input-1-j));
    		pt = pt->next;
    	}

        gate_struct* move = gate;

		//printf("----------------------\n");

        while(move!=NULL)
        {
		// input

			//printf("move->input1:%s\n", move->input1);
			if (is_CAPS(move->input1[0])==0) {
				num1 = find_input_name(move->input1,in_head);
			}else {
				num1 = find_input_name(move->input1,temphead);
			}

			if (strcmp(move->name,"NOT")!=0)
			{
				//printf("move->input2:%s\n", move->input2);
				if (is_CAPS(move->input2[0])==0) {
					num2 = find_input_name(move->input2,in_head);
				}else {
					num2 = find_input_name(move->input2,temphead);
				}
			}

		//find gate output

 			if(strcmp(move->name,"AND")==0) {
				num3 = and_gate(num1,num2);
      		}
 			else if(strcmp(move->name,"OR")==0) {
				num3 = or_gate(num1,num2);
    		}
            else if(strcmp(move->name,"NAND")==0) {
				num3 = nand_gate(num1,num2);
			}
 			else if(strcmp(move->name,"NOR")==0) {
				num3 = nor_gate(num1,num2);
      		}
 			else if(strcmp(move->name,"XOR")==0) {
				num3 = xor_gate(num1,num2);
      		}
			else if(strcmp(move->name,"NOT")==0) {
				num2 = not_gate(num1);
            }
   			else if(strcmp(move->name,"DECODER")==0) {
				// decoder logic goes here...
            }
  			else if(strcmp(move->name,"MULTIPLEXER")==0) {
				// mux logic goes here...
            }

		// output

			if ( (strcmp(move->name,"NOT")!=0) && (strcmp(move->name,"MULTIPLEXER")!=0) && (strcmp(move->name,"DECODER")!=0) )
			{
				if(is_CAPS(move->output[0])==0){
					bl = find_output_name(move->output,num3,out_head);
				}
				else{
					bl = find_output_name(move->output,num3,temphead);
					if(bl==2){
						temphead = create_num_struct(temphead,move->output);
						bl = find_output_name(move->output,num3,temphead);
					}
				}
			}
			else if (strcmp(move->name,"NOT")==0)
			{
     			if(is_CAPS(move->output[0])==0){
                    bl = find_output_name(move->output,num2,out_head);
                }
                else {
                    bl = find_output_name(move->output,num2,temphead);
                    if (bl==2) {
                        temphead = create_num_struct(temphead,move->output);
                        bl = find_output_name(move->output,num2,temphead);
                    }
                }
            }
			num1 = bl;
    	    move = move->next;
    	} // end of move while

        free_gate_struct(&move);		// check if it does NOT affect "gate"
		//if (move==NULL) printf("move memory deleted.....\n");

        //Printing FINAL OUTPUT
        //printf("%d\n", out_head->valid);
		num_struct* ag = out_head;
        print_output(&ag);

    }   // end of input while loop

	fclose(in_file);

	// De-allocate/Free memory

    free_num_struct(&temphead);
		//if (temphead==NULL) printf("temphead memory deleted.....\n");
	free_gate_struct(&gate);
		//if (gate==NULL) printf("gate memory deleted.....\n");
	free_num_struct(&in_head);
		//if (in_head==NULL) printf("in_head memory deleted.....\n");
	free_num_struct(&out_head);
		//if (out_head==NULL) printf("out_head memory deleted.....\n");

    return 0;
}