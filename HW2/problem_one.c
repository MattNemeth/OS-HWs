//Problem One

int main(int argc, char* argv[]){
	if(argc > 3){
		printf("Too many arguments... Program only takes 2 input arguments.\n");
		exit(0);
	}else if(argc < 3){
		printf("Too few arguments... Program only takes 2 input arguments.\n");
		exit(0);
//	}else if(!isdigit(*argv[1])){
	//	printf("The argument passed in must be an integer...\n");
	//	exit(0);
	}else{
	//	printFunction(atoi(argv[1]));
		fork();
		exec(argv[1]);	//Execute the program that was passed in
	}
	return 0;
}

