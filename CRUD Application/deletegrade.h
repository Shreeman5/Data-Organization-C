int check_valid_class_id(int class_id);
int check_valid_id(int class_id, int assignment_id);
int check_valid_ssn(int class_id, char *SSN);

void delete_grade(int class_id, int assignment_id, char *SSN)
{
  printf("%d\n", class_id);
  printf("%d\n", assignment_id);
  printf("%s\n", SSN);

  if(strlen(SSN) != 9)
  {
    printf("Please enter social security number of 9 characters\n");
    return;
  }

  char social[9];
  memcpy(social, SSN, 9);

  if(check_valid_class_id(class_id) && check_valid_id(class_id, assignment_id) && check_valid_ssn(class_id, social))
  {
    FILE *fp;
    struct grades data;
    int found = 0;
    int counter = 0;
    int response = 0;
    int i;
    
    fp = fopen("grades.db", "r");
    if(fp == NULL)
    {
	printf("\n Error: Cannot open assignment file");
	exit(1);
    }
    while(fread(&data, sizeof(struct grades), 1, fp))
    {
      if(data.assignment_id == assignment_id && (strncmp(data.ssn, social, 9) == 0))
      {
	printf("dank memes\n");
        found = 1;
	break;
      }
      counter++;
    }

    if(! found)
    {
      printf("not found in the database\n");
      fclose(fp);
      return;
    }
    else
    {
      found = 0;
      fseek(fp, counter*sizeof(struct grades), SEEK_SET);
      fread(&data, sizeof(struct grades), 1, fp);
      printf("Are you sure you want to delete Points = %d , AssignmentID = %d SSN = ", data.point, data.assignment_id);
      for (i = 0; i < 9; i++)
      {
	printf("%c",data.ssn[i]);
      }
      printf(" from the database? [Y/N] ");
      
      rewind(fp);
      response = getchar();
      getchar();
      if(response == 'Y')
      {
	FILE *fp_tmp;
	fp_tmp = fopen("tmp.db", "w");
	if(fp_tmp == NULL)
	{
	    printf("\n Error: Cannot open file");
            exit(1);
	}
	while (fread(&data, sizeof(struct grades), 1, fp))
	{
	  if(data.assignment_id == assignment_id && (strncmp(data.ssn, social, 9) == 0))
          {
	    printf("A record with requested name found and deleted.\n\n");
      	    found = 1;
	  }
	  else
          {
	    fwrite(&data, sizeof(struct grades), 1, fp_tmp);
	  }
	}

	fp = fp_tmp;
        fclose(fp);
	remove("grades.db");
        rename("tmp.db", "grades.db");
	return;
      }
      else
      {
	printf("dang son\n");
      }
    }
    fclose(fp);
  }
  else
  {
    printf("wack\n");
  }
}


void delete_grade_data_menu()
{
  char classID[10];
  int class_id;
  char assignmentID[10];
  int assignment_id;
  char SSN[12];

  printf("Enter Class ID or (-1 for Class List): ");
  fgets(classID, 10, stdin);
  class_id = atoi(classID);

  if(class_id == -1)
  {
    view_class_data_menu();
    delete_grade_data_menu();
    return;
  }

  printf("Enter Assignment ID or (-1 for Assignment List): ");
  fgets(assignmentID, 10, stdin);
  assignment_id = atoi(assignmentID);

  while(assignment_id == -1)
  {
    view_assignment(class_id);
    printf("Enter Assignment ID or (-1 for Assignment List): ");
    fgets(assignmentID, 10, stdin);
    assignment_id = atoi(assignmentID);
  }

  printf("Enter SSN: ");
  fgets(SSN, 12, stdin);
  if(strlen(SSN) > 10)
  {
    printf("SSN should have 9 characters\n");
    return;
  }
  else if(strlen(SSN) < 10)
  {
    printf("SSN should have 9 characters\n");
    return;
  }
  else
  {
    delete_endline_ssn(SSN);
  }

  

  printf("CID = %d, AID = %d, SSN = %s\n", class_id, assignment_id, SSN);
  
  delete_grade(class_id, assignment_id, SSN);
}
