void view_student_enrollment(int class_id)
{
  int i;
  char social[9];
  FILE *fp;

  struct enrollment data;
  fp = fopen("enrollment.db", "r");

  if(fp == NULL)
  {
    printf("\n Error: Cannot open file");
    exit(1);
  }

  printf("\n\nEnrollment in the database\n");
  while(fread(&data, sizeof(struct enrollment), 1, fp))
  {
    if(data.id == class_id)
    {
      printf("Class ID: %d, Student: ", data.id);
      memcpy(social, data.ssn, 9);
      for (i = 0; social[i] != '\0'; i++)
      {
	printf("%c",social[i]);
      }
      printf(" Status: Enrolled");
      printf("\n");
    }
  }
  printf("\n\n");
  fclose(fp);
  return;
}

void view_enrollment_data_menu()
{
  char classID[10];
  int class_id;

  printf("Enter Class ID or (-1 for Class List): ");
  fgets(classID, 10, stdin);
  class_id = atoi(classID);

  if(class_id == -1)
  {
    view_class_data_menu();
    view_enrollment_data_menu();
    return;
  }

  //printf("CID: %d\n", class_id);
  view_student_enrollment(class_id);
}
