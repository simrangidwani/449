//Simran Gidwani srg61@pitt.edu

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int numOfArgs;

struct ID3tag{
	char tagID[3];
	char title[30];
	char artist[30];
	char album[30];
	char year[4];
	char comment[28];
	char zero_sep;
	char trackNum;
	char genre;
} Tag;

void printList()
{
	printf("\nTitle: ");
	for (int i = 0; i < 30; i++)
	{
		printf("%c", Tag.tagID[i]);
	}
	printf("\nArtist: ");
	for (int i = 0; i < 30; i++)
	{
		printf("%c", Tag.artist[i]);
	}
	printf("\nAlbum: ");
	for (int i=0; i < 30; i++)
	{
		printf("%c", Tag.album[i]);
	}
	printf("\nYear: ");
	for (int i=0; i<4; i++)
	{
		printf("%c", Tag.year[i]);
	}
	printf("\nComments: ");
	for (int i=0; i< 28; i++)
	{
		printf("%c", Tag.comment[i]);
	}
	printf("\nTrack Number: ");
	printf("%d", Tag.trackNum);	
}

int main(int argc, char * argv[])
{
	struct Tag;
	numOfArgs = argc;
	FILE *file;
	file = fopen(argv[1], "r+b");
	if (file == NULL)
	{
		printf("File cannot be opened.");
		fclose(file);
		exit(0);
	}
	fseek(file, -128, SEEK_END);  //takes you to the beginning of the file
	fread(&Tag.tagID, sizeof(&Tag.tagID), 1, file);
	int tagExists = strncmp(Tag.tagID, "TAG", 1);
	if (numOfArgs == 1)
	{
		printf("To use this program: \n"
			"On the command line enter the name of file you would \n"
			"like to read from. This will print out the contents of the \n"
			"mp3 file. Entering another argument of a field on the command \n"
			"line after the file name will enable you to edit the contents \n"
			"of the file.");
	}

	else if (numOfArgs == 2)  //only argument is the file name
	{
		if (tagExists == 0)
		{
			fseek(file, -sizeof(&Tag.tagID), SEEK_CUR); //goes 3 from beginning
			fread(&Tag, sizeof(struct ID3tag), 1, file);
			printList();
		}
		else
		{
			printf("\nNo ID3 tag.");
		}
	}
	else if (numOfArgs > 2)
	{
		if (tagExists == 0)
		{
			fseek(file, -sizeof(&Tag.tagID), SEEK_CUR);	
			for (int i = 2; i < numOfArgs; i++)
			{
				if (strcmp(argv[i], "-title") == 0)
				{
					strncpy(Tag.title, argv[i+1], 30);
					fseek(file, -125, SEEK_END);
					fwrite(&Tag, sizeof(&Tag.title), 1, file);
				}
				else if (strcmp(argv[i], "-artist") == 0)
				{
					strncpy(Tag.artist, argv[i+1], 30);
					fseek(file, -95, SEEK_END);
					fwrite(&Tag, sizeof(&Tag.artist), 1, file);
				}
				else if (strcmp(argv[i], "-album") == 0)
				{
					strncpy(Tag.artist, argv[i+1], 30);
					fseek(file, -65, SEEK_END);
					fwrite(&Tag, sizeof(&Tag.album), 1, file);
				}
				else if (strcmp(argv[i], "-year") == 0)
				{
					strncpy(Tag.year, argv[i+1], 4);
					fseek(file, -35, SEEK_END);
					fwrite(&Tag, sizeof(&Tag.year), 1, file);
				}
				else if (strcmp(argv[i], "-comment") == 0)
				{
					strncpy(Tag.comment, argv[i+1], 28);
					fseek(file, -31, SEEK_END);
					fwrite(&Tag, sizeof(&Tag.comment), 1, file);
				}
				else if (strcmp(argv[i], "-track") == 0)
				{
					int numTrack = atoi(argv[i+1]);
					Tag.trackNum = numTrack;
					fseek(file, -3, SEEK_END);
					fwrite(&Tag, sizeof(&Tag.trackNum), 1, file);
				}
				else if (strcmp(argv[i], "-genre") == 0)
				{
					Tag.genre = *argv[i+1];
					fseek(file, -2, SEEK_END);
					fwrite(&Tag, sizeof(&Tag.genre), 1, file);
				}
				else
					continue;
				i++;
			}
			fwrite(&Tag, sizeof(struct ID3tag), 1, file);
		}

		else if (tagExists!=0)
		{
			fseek(file, 0, SEEK_END);
			strcpy(Tag.tagID, "TAG");
			for (int i = 2; i < numOfArgs; i++)
			{
				if (strcmp(argv[i], "-title") == 0)
				{
					strncpy(Tag.title, argv[i+1], 30);
				}
				else if (strcmp(argv[i], "-artist") == 0)
				{
					strncpy(Tag.artist, argv[i+1], 30);
				}
				else if (strcmp(argv[i], "-album") == 0)
				{
					strncpy(Tag.artist, argv[i+1], 30);
				}
				else if (strcmp(argv[i], "-year") == 0)
				{
					strncpy(Tag.year, argv[i+1], 4);
				}
				else if (strcmp(argv[i], "-comment") == 0)
				{
					strncpy(Tag.comment, argv[i+1], 28);
				}
				else if (strcmp(argv[i], "-track") == 0)
				{
					int numTrack = atoi(argv[i+1]);
					Tag.trackNum = numTrack;
				}
				else if (strcmp(argv[i], "-genre") == 0)
				{
					Tag.genre = *argv[i+1];
				}
				else
					continue;
				i++;
			}
			fwrite(&Tag, sizeof(struct ID3tag), 1, file);
		}
		printList();
	}
	fclose(file);
}
