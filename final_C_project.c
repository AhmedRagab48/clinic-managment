#include "AR_STD_TYPES.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DPassword 1234
#define M_char 100 
#define NULL_ptr (void*) 0
/*patient node */
typedef struct patient
{
   u8 Name[M_char];
   u8 gender[M_char];
   u32 age;
   u16 id;
   struct patient *Next;
} Patient_t;
/*******/
u32 Selected_slot[5];
Patient_t *Head;
Patient_t *last;
u16 PatientNum = 0;
u8 *fixed_id;
u32 slot_counter; 
u16 slotID[M_char];
/****function declarition*****/
void addPatient();
void displayPatientInformation(u16 ID);
void EditPtientRecord(u16 id);
u16 checkForId(u16 ID);
void reserveSlote(u16 ID);
void cancelReserveSlote(u16 ID);
void ShowToDayResevation();
void main()
{
   while (1)
   {
      u16 choice;
      u16 ID;
      u16 pasword;
      u16 admin;
      u16 ID_Cheak;
      /*********************************************************************/
      printf("****HALLO****\n");
      printf("for user mode enter (1) || for admin mode enter (2)\n");
      printf("Your choice :  ");
      scanf("%d", &choice);
      if (choice == 1)
      {     
         u16 local_C;
         u16 UserID;
         printf("for display Patient Information press (1)\n");
         printf("for display today reservation press (2)\n");
         printf("your choice : ");
         scanf("%d",&local_C);
         switch (local_C)
         {
         case 1:
            printf("pleas input the patient ID : ");
            scanf("%d", &UserID);
            if (checkForId(UserID) != 0)
            {
               displayPatientInformation(UserID);
            }
            else
            {
               printf("invalid ID\n");
            }  
               break;
         case 2:
            ShowToDayResevation();      
            break;        
         default:
            printf("wrong choice \n");
            break;
         }
      }
      else if (choice == 2)
      {
         for (u16 i = 0; i < 3; i++)
         {
            printf("pleas enter the pasword : ");
            scanf("%d", &pasword);
            printf("************************************\n");
            if (pasword == DPassword)
            {
               printf("the password is correct Hallo sar \n");
               printf("to add new patient enter (1) \n\nto edit patient record inter (2)\n\nto Reserve a slot with the doctor (3)\n\ntoCancel reservation inter (4)\n\n");
               printf("Your choice :  ");
               scanf("%d", &admin);
               switch (admin)
               {
                      /*****Add new patient record****/
                  case 1:
                        addPatient();break;
                  case 2:
                        /***************Edit patient record**************/
                           printf("pleas inter the ID of the patient : \n");
                           scanf("%d",&ID_Cheak);
                           if (checkForId(ID_Cheak)!=0)
                           {
                              printf("the id is exist \n");
                              EditPtientRecord(ID_Cheak); break;
                           }
                           break;
                  case 3:
                           printf("pleas inter the ID of the patient : ");
                           scanf("%d",&ID_Cheak);
                           if (checkForId(ID_Cheak)!=0)
                           {
                              u16 id = ID_Cheak;
                              reserveSlote(id);
                           }
                           else printf("invild id\n");
                           break;
                  case 4:
                           printf("pleas inter your id : ");
                           scanf("%d",&ID_Cheak);
                           cancelReserveSlote(ID_Cheak);
                           break;
               } break;
            }
            else
            {
               printf("incorrect password pleas try again \n");
               if (i == 2)
               {
                  printf("you reached the maximum number of attempts try later \n");
                  break;
               }
            } 
         }
      }
   }
}
void addPatient()
{
   
    Patient_t *node=(Patient_t*) malloc (sizeof(Patient_t));
    printf("\nplease enter patient's name: ");
    scanf("%s",&node->Name);
    printf("\nplease enter patient's gender: ");
    scanf("%s",&node->gender);
    printf("\nplease enter patient's age: ");
    scanf("%d",&node->age);
    printf("\nplease enter patient's ID: ");

    u32 new_id;
    scanf("%d",&new_id);
    while(checkForId(new_id)!=0)
    {
        printf("Repeated ID, please enter a valid ID: ");
        scanf("%d",&new_id);
    }
    node->id=new_id;

    if(Head==NULL_ptr)
    {
        Head=node;
    }
    else
    {
        last->Next=node;
    }
    last=node;
    node->Next=NULL_ptr;
}

void displayPatientInformation(u16 ID)
{
   Patient_t *node = Head;
   while (ID != node->id)
   {
      node = node->Next;
   }
   printf("the information of patient with ID : %d \n", ID);
   printf("the patient name is : %s\n", node->Name);
   printf("the patient gender : %s\n", node->gender);
   printf("the patient age :%hu\n", node->age);
}
u16 checkForId(u16 ID)
{
   u16 local_counter = 0;
   Patient_t *node;
   node = Head;
   while (node != NULL_ptr)
   {
      if (node->id == ID)
      {
         local_counter++;
         break;
      }
      node = node->Next;
   }
   return local_counter;
}

void EditPtientRecord(u16 id)
{
  Patient_t *node = Head;
   while(node != NULL_ptr )
  {
     if (node->id = id)
     {
         printf("\nthe patient name :");
         scanf("%s", node->Name);
         printf("\nthe patient gender :");
         scanf("%s", node->gender);
         printf("\nthe patient id :");
         scanf("%d", &node->id);
         printf("\nthe patient age :");
         scanf("%d", &node->age);
         node->Next = NULL_ptr;
         break;
     }
     else
     {
         node = node->Next;
     }
  }

}
void reserveSlote(u16 ID)
{
   u32 choice;
   Patient_t *node = Head;
   while(node != NULL_ptr )
   {
      if (checkForId(ID)==0)
      {
         printf("\n pleas inter valid ID");
      }
      else
      { 
         printf("\nValid ID\n");
         if (slot_counter==0)
         {
            slotID[0]=ID;
            slot_counter=1;
            printf("\nthere are 3 available slots");
            printf("\n(1) 2pm to 2:30pm\n(2) 2:30pm to 3pm\n(3) 3pm to 3:30pm\n");
            printf("\nyour choice : ");
            scanf("%d",&choice);
            switch (choice)
            {
               case 1:
                  Selected_slot[0]=1;
                  if (Selected_slot[0]==1)
                  {
                     printf("you have aslot at 2pm \n");
                  }
                  break;
               case 2:
                  Selected_slot[0]=2;
                  if (Selected_slot[0]==2)
                  {
                     printf("you have aslot at 2:30pm \n");
                  }
                  break;
               case 3:
                  Selected_slot[0]=3;
                  if (Selected_slot[0]==3)
                  {
                     printf("you have aslot at 3pm \n");
                  }
                break;     
               default:
                  printf("Wrong choice");
                  break;
               }
         }
         else if (slot_counter==1)
         {
            slotID[1]=ID;
            slot_counter=2;
            if ( Selected_slot[0] = 1 )
            {
               printf("two slots is avilable\n");
               printf("(1) 2:30pm to 3pm\n\n(2) 3pm to 3:30pm\n");
               printf("your choice: ");
               scanf("%d",&choice);
               switch (choice)
                {
                  case 1:
                     printf("you have aslot at 2:30pm \n");
                     Selected_slot[2]=1;  
                     break;
                  case 2:
                     printf("you have aslot at 3pm \n");
                     Selected_slot[3]=1;
                     break;     
                  default:
                     printf("Wrong choice");
                     break;                    
                }
            }
            else if ( Selected_slot[0] = 2)
            {
               printf("two slots is avilable\n");
               printf("(1) 2pm to 2:30pm\n\n(2) 3pm to 3:30pm\n");
               printf("your choice:\n");
               scanf("%d",&choice);
               switch (choice)
               {
                  case 1:
                     printf("you have aslot at 2pm \n");
                     Selected_slot[1]=1;
                     break;
                  case 2:
                     printf("you have aslot at 3pm \n");
                     Selected_slot[3]=1;
                     break;    
                  default:
                     printf("Wrong choice");
                     break;

               }
            }
            else
            {
               printf("two slots is avilable\n");
               printf("(1) 2pm to 2:30pm\n\n(2) 2:30pm to 3pm\n\n");
               printf("your choice");
               scanf("%d",&choice);
               switch (choice)
               {
                  case 1:
                     printf("you have aslot at 2pm \n");
                     Selected_slot[1]=1;
                     break;
                  case 2:
                     printf("you have aslot at 2:30pm \n");
                     Selected_slot[2]=1;   
                     break;
                  default:   
                     printf("Wrong choice");
                     break;
               }
            }break;
         }
         else
         {
            slotID[3]=ID;
            if (Selected_slot[2] = 1)
            {
               if ( Selected_slot[3] = 1)
               { 
                  printf("one slots is avilable\n");
                  printf("you have aslot at 2pm \n");
                  break;
               }
               else if(Selected_slot[1] = 1)
               {
                  printf("one slots is avilable\n");
                  printf("you have aslot at 3 pm \n");
                  break;
               }
            }
            else if (Selected_slot[3] = 1)
            {
               if (Selected_slot[1] = 1)
               {
                  printf("one slots is avilable\n");
                  printf("you have aslot at 2:30pm \n");
                  break;
               } 
            } 
         }
      }
      break;
   }
}  
void cancelReserveSlote(u16 ID)
{
   u32 choice;
   Patient_t *node = Head;
   while(node != NULL_ptr )
   {
      if (checkForId(ID)==0)
      {
         printf("pleas inter valid ID\n");
      }
      else
      {
         printf("valid ID\n");
         if (slot_counter==1)
         {
            slot_counter=0;
            Selected_slot[0]=0;
            printf("the slot is canceled\n");
         }
         else if (slot_counter==2)
         {
            slot_counter=1;
            printf("pleas input the slot which u want to cancel\n");
            printf("chose you slot carefully\n");
            printf("(1) 2pm to 2:30pm\n(2) 2:30pm to 3pm\n(3) 3pm to 3:30pm\n");
            printf("your choice :  ");
            scanf("%d",&choice);
            if (choice==1)
            {
               Selected_slot[1]=0;
               printf("the slot is canceled\n");
            }
            else if (choice==2)
            {
               Selected_slot[2]=0;
               printf("the slot is canceled\n");
            }
            else if (choice==3)
            {
               Selected_slot[3]=0;
               printf("the slot is canceled\n");
            }
            else
            {
            printf("wrong choice \n");
            break;
            }
         }
      }
      break; 
   }  
}    
/******/
void ShowToDayResevation()
{
   if (slot_counter==0)
   {
     printf("NO RESERVATION TO DAY \n");
   }
   else if (slot_counter==1)
   {
      printf("one slot today \n");
      if (Selected_slot[0]==1)
      {
         printf("the patient with id (%d) has slot at 2pm\n",slotID[0]);
      }
      else if (Selected_slot[0]==2)
      {
         printf("the patient with id (%d) has slot at 2:30pm\n",slotID[0]);
      }
      else if (Selected_slot[0]==3)
      {
         printf("the patient with id (%d) has slot at 3pm\n",slotID[0]);
      }
   }
   else if (slot_counter==2)
   {
      printf("Two slot today \n");
      if (Selected_slot[2]==1)
      {
         if (Selected_slot[0]==1)
         {
            printf("the patient with id (%d) has slot at 2pm\n",slotID[0]);
            printf("the patient with id (%d) has slot at 2:30pm\n",slotID[1]);
         }
         else if (Selected_slot[2]==1)
         {
            if (Selected_slot[0]==3)
            {
               printf("the patient with id (%d) has slot at 2:30pm\n",slotID[1]);
              printf("the patient with id (%d) has slot at 3pm\n",slotID[0]);
            }
         }
      }
      else if (Selected_slot[1]==1)
      {
         if (Selected_slot[0]==2)
         {
            printf("the patient with id (%d) has slot at 2:30pm\n",slotID[0]);
            printf("the patient with id (%d) has slot at 2pm\n",slotID[1]);
         }
         else if (Selected_slot[1]==1)
         {
            if (Selected_slot[0]==3)
            {
               printf("the patient with id (%d) has slot at 2pm\n",slotID[1]);
               printf("the patient with id (%d) has slot at 3pm\n",slotID[0]);
            }
         }
      }
      else if (Selected_slot[3]==1)
      {
         if (Selected_slot[0]==2)
         {
            printf("the patient with id (%d) has slot at 2:30pm\n",slotID[0]);
            printf("the patient with id (%d) has slot at 3pm\n",slotID[1]);
         }
         else if (Selected_slot[3]==1)
         {
            if (Selected_slot[0]==1)
            {
               printf("the patient with id (%d) has slot at 2pm\n",slotID[0]);
               printf("the patient with id (%d) has slot at 3pm\n",slotID[1]);
            }
         }
      }
   }
   else if (slot_counter==3)
   {
      printf("three slot today \n");
      printf("the patient with id (%d) has slot at 2pm\n",slotID[0]);
      printf("the patient with id (%d) has slot at 2:30pm\n",slotID[1]);
      printf("the patient with id (%d) has slot at 3pm\n",slotID[3]);
   }
}


   