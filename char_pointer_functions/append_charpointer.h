//append char pointer and char array to sourcechar
//sourcechar = append("123456", "789");
//123456789
char * append(char * sourcechar, char * appendedchar){
	int i = 0;
	char temp[strlen(sourcechar)];
	for(i = 0; i < strlen(sourcechar); i++){
		temp[i] = sourcechar[i];
	}
	temp[i] = '\0';
	sourcechar = (char *) malloc ((sizeof(char) * strlen(sourcechar)) + (sizeof(char) * strlen(appendedchar)));
	for(i = 0; i < strlen(temp); i++){
		sourcechar[i] = temp[i];
	}
	for(i = 0; i < strlen(appendedchar); i++){
		sourcechar[i + strlen(temp)] = appendedchar[i];
	}
	sourcechar[strlen(temp) + strlen(appendedchar)] = '\0';
	return sourcechar;
}

char * appendc(char * sourcechar, char appendedchar){
	int i = 0;
	char temp[strlen(sourcechar)];
	for(i = 0; i < strlen(sourcechar); i++){
		temp[i] = sourcechar[i];
	}
	temp[i] = '\0';
	sourcechar = (char *) malloc ((sizeof(char) * strlen(sourcechar)) + (sizeof(char) * 1));
	for(i = 0; i < strlen(temp); i++){
		sourcechar[i] = temp[i];
	}
	sourcechar[i] = appendedchar;
	
	sourcechar[i + 1] = '\0';
	return sourcechar;
}