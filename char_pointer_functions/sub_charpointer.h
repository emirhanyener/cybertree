char * substr(char * sourcechar, int length){
	int i = 0;
	if(length >= strlen(sourcechar)){
		length = strlen(sourcechar);
	}
	char * temp = (char *) malloc (sizeof(char) * strlen(sourcechar) - length);
	for(i = 0; i < length; i++){
		temp[i] = sourcechar[i];
	}
	temp[i] = '\0';
	
	return temp;
}

char * substrs(char * sourcechar, int length, int start){
	int i = 0;
	
	if(start >= strlen(sourcechar)){
		return sourcechar;
	}
	if(length >= strlen(sourcechar) - start){
		length = strlen(sourcechar) - start;
	}
	char * temp = (char *) malloc (sizeof(char) * strlen(sourcechar) - length - start);
	for(i = 0; i < length - start + 1; i++){
		temp[i] = sourcechar[i + start];
	}
	temp[i] = '\0';
	
	return temp;
}