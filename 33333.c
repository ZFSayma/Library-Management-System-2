#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void AddBook();
void DeleteBook();
void UpdateBook();
void ViewAllBooks();
void SearchBook();
void IsBookAvailable();
void RegisterUser();
void BorrowBook();
void ReturnBook();
void CalculateFine();
void Exit();

struct Book {
    int id;
    char title[100];
    char author[50];
    char subject[50];
    int isAvailable; // 1 = available, 0 = borrowed
};

FILE* fp;
FILE* temp;

int main()
{
    int choice=0;

    printf("\n\t\t---WELCOME TO STUDENT LIBRARY---\t\t\n");
   do
    {
        printf("\n\t\t---MENU---\t\t\n");
        printf("\t\t1. Add a New Book\n2. Delete a Book\n3. Update Book Information\n4.View All Books\n5.Search for a Book\n6. Check Book Availability\n7. Register a New User\n8. Borrow a Book\n9. Return a Book\n10. Calculate Fine for Late Return\n11.Exit\n");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                    AddBook();
                    break;
            case 2:
                    DeleteBook();
                    break;
            case 3:
                    UpdateBook();
                    break;
            case 4:
                    ViewAllBooks();
                    break;
            case 5:
                    SearchBook();
                    break;
            case 6:
                    IsBookAvailable();
                    break;
            case 7:
                    RegisterUser();
                    break;
            case 8:
                    BorrowBook();
                    break;
            case 9:
                    ReturnBook();
                    break;
            case 10:
                    CalculateFine();
                    break;
            case 11:
                    Exit();
            default:
                    printf(" ! Invalid Input...\n");

        }
    }while(choice!=11);
}

void AddBook()
{
    struct Book newBook;

    fp = fopen("books.txt","a+");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter Book ID: ");
    scanf("%d",&newBook.id);
    getchar();

    printf("Enter Book Title: ");
    fgets(newBook.title,sizeof(newBook.title),stdin);
    newBook.title[strcspn(newBook.title, "\n")] = '\0';

    printf("Enter Author Name: ");
    fgets(newBook.author, sizeof(newBook.author), stdin);
    newBook.author[strcspn(newBook.author, "\n")] = '\0';

    printf("Enter Subject: ");
    fgets(newBook.subject, sizeof(newBook.subject), stdin);
    newBook.subject[strcspn(newBook.subject, "\n")] = '\0';

    newBook.isAvailable = 1; // Newly added book is available by default

    fprintf(fp, "%d|%s|%s|%s|%d\n", newBook.id, newBook.title, newBook.author, newBook.subject, newBook.isAvailable);

    fclose(fp);

    printf("\nBook added successfully!\n");
}

void ViewAllBooks()
{
    struct Book book;

    fp = fopen("books.txt","r");
    if (fp == NULL) {
        printf("Error: Could not open books.txt file!\n");
        return;
    }
    printf("\n========== Book List ==========\n");
    printf("%-5s %-25s %-20s %-15s %-10s\n", "ID", "Title", "Author", "Subject", "Status");
    printf("--------------------------------------------------------------------------\n");

    while(fscanf(fp,"%d|%[^|]|%[^|]|%[^|]|%d\n",&book.id,book.title,book.author,book.subject,&book.isAvailable)==5)
    {
         printf("%-5d %-25s %-20s %-15s %-10s\n",book.id, book.title, book.author, book.subject,book.isAvailable ? "Available" : "Borrowed");
    }
    fclose(fp);
}

void SearchBook()  //Search Book by title
{
    struct Book book;
    char searchTitle[100];

    fp = fopen("books.txt","r");
    if(fp==NULL){
        printf("Error opening books.txt file\n");
        return;
    }

    printf("Enter the title to search\n");
    getchar();

    fgets(searchTitle,sizeof(searhTitle),stdin);
    searchTitle[strcspn(searchTitle, "\n")] = '\0';

    while (fscanf(fp, "%d|%[^|]|%[^|]|%[^|]|%d\n", &book.id, book.title, book.author, book.subject, &book.isAvailable) == 5) {
        if (strcasecmp(book.title, searchTitle) == 0) {
            printf("\nBook Found:\n");
            printf("ID: %d\nTitle: %s\nAuthor: %s\nSubject: %s\nStatus: %s\n",
                   book.id, book.title, book.author, book.subject,
                   book.isAvailable ? "Available" : "Borrowed");
            found = 1;
            break;
        }
    }
     if (!found)
        printf("Book not found!\n");

    fclose(fp);
}

void DeleteBook()
 {

    struct Book book;
    int deleteID, found = 0;

    printf("Enter Book ID to delete: ");
    scanf("%d", &deleteID);

    fp = fopen("books.txt", "r");
    temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("File error!\n");
        return;
    }

    while (fscanf(fp, "%d|%[^|]|%[^|]|%[^|]|%d\n", &book.id, book.title, book.author, book.subject, &book.isAvailable) == 5) {
        if (book.id == deleteID) {
            found = 1; // skip writing this book
        } else {
            fprintf(temp, "%d|%s|%s|%s|%d\n", book.id, book.title, book.author, book.subject, book.isAvailable);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (found)
        printf("Book deleted successfully!\n");
    else
        printf("Book ID not found!\n");
}

void UpdateBook()
{

}

void IsBookAvailable()
{

}

void RegisterUser()
{

}

void BorrowBook()
{

}

void ReturnBook()
{

}

void CalculateFine()
{

}

void Exit()
{
    exit(0);
}

