#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Book
{
    char *title;
    char *authors;
    int year;
    char *distributor;
    int rate;
    int cost;
    int ID;

    struct Book *smaller;
    struct Book *larger;
    struct Book *parent;
};

struct Book *books = NULL;
int globalBooksCounter = 0;
int globalIDCounter = 0;

struct Book *createBook(char *title, char *authors, int year, char *distributor, int rate, int cost)
{
    struct Book *newBook = (struct Book *)malloc(sizeof(struct Book));

    if (newBook == NULL)
    {
        fprintf(stderr, "Could not allocate memory\n");
        return NULL;
    }

    newBook->title = (char *)malloc(sizeof(char) * (strlen(title) + 1));
    newBook->authors = (char *)malloc(sizeof(char) * (strlen(authors) + 1));
    newBook->distributor = (char *)malloc(sizeof(char) * (strlen(distributor) + 1));

    newBook->title = title;
    newBook->authors = authors;
    newBook->year = year;
    newBook->distributor = distributor;
    newBook->rate = rate;
    newBook->cost = cost;
    newBook->ID = globalIDCounter++;

    newBook->smaller = NULL;
    newBook->larger = NULL;
    newBook->parent = 0x0;

    return newBook;
}

void normiliseRoot()
{
    while (books->parent != NULL)
        books = books->parent;
}

int compareBooksByName(struct Book *first, struct Book *second)
{

    if (first == NULL || second == NULL)
        return 0;

    if (strcmp(first->title, second->title))
        return strcmp(first->title, second->title);
    if (strcmp(first->authors, second->authors))
        return strcmp(first->authors, second->authors);
    if (first->year - second->year)
        return first->year - second->year;
    if (strcmp(first->distributor, second->distributor))
        return strcmp(first->distributor, second->distributor);
    if (first->rate - second->rate)
        return first->rate - second->rate;
    if (first->cost - second->cost)
        return first->cost - second->cost;
    return 0;
}

int compareBooksByAuthors(struct Book *first, struct Book *second)
{

    if (first == NULL || second == NULL)
        return 0;

    if (strcmp(first->authors, second->authors))
        return strcmp(first->authors, second->authors);
    if (strcmp(first->title, second->title))
        return strcmp(first->title, second->title);
    if (first->year - second->year)
        return first->year - second->year;
    if (strcmp(first->distributor, second->distributor))
        return strcmp(first->distributor, second->distributor);
    if (first->rate - second->rate)
        return first->rate - second->rate;
    if (first->cost - second->cost)
        return first->cost - second->cost;
    return 0;
}

int compareBooksByYear(struct Book *first, struct Book *second)
{

    if (first == NULL || second == NULL)
        return 0;

    if (first->year - second->year)
        return first->year - second->year;
    if (strcmp(first->title, second->title))
        return strcmp(first->title, second->title);
    if (strcmp(first->authors, second->authors))
        return strcmp(first->authors, second->authors);
    if (strcmp(first->distributor, second->distributor))
        return strcmp(first->distributor, second->distributor);
    if (first->rate - second->rate)
        return first->rate - second->rate;
    if (first->cost - second->cost)
        return first->cost - second->cost;
    return 0;
}

int compareBooksByDistributor(struct Book *first, struct Book *second)
{

    if (first == NULL || second == NULL)
        return 0;

    if (strcmp(first->distributor, second->distributor))
        return strcmp(first->distributor, second->distributor);
    if (strcmp(first->title, second->title))
        return strcmp(first->title, second->title);
    if (strcmp(first->authors, second->authors))
        return strcmp(first->authors, second->authors);
    if (first->year - second->year)
        return first->year - second->year;
    if (first->rate - second->rate)
        return first->rate - second->rate;
    if (first->cost - second->cost)
        return first->cost - second->cost;
    return 0;
}

int compareBooksByRate(struct Book *first, struct Book *second)
{

    if (first == NULL || second == NULL)
        return 0;

    if (first->rate - second->rate)
        return first->rate - second->rate;
    if (strcmp(first->title, second->title))
        return strcmp(first->title, second->title);
    if (strcmp(first->authors, second->authors))
        return strcmp(first->authors, second->authors);
    if (first->year - second->year)
        return first->year - second->year;
    if (strcmp(first->distributor, second->distributor))
        return strcmp(first->distributor, second->distributor);
    if (first->cost - second->cost)
        return first->cost - second->cost;
    return 0;
}

int compareBooksByCost(struct Book *first, struct Book *second)
{

    if (first == NULL || second == NULL)
        return 0;

    if (first->cost - second->cost)
        return first->cost - second->cost;
    if (first->rate - second->rate)
        return first->rate - second->rate;
    if (strcmp(first->title, second->title))
        return strcmp(first->title, second->title);
    if (strcmp(first->authors, second->authors))
        return strcmp(first->authors, second->authors);
    if (first->year - second->year)
        return first->year - second->year;
    if (strcmp(first->distributor, second->distributor))
        return strcmp(first->distributor, second->distributor);
    return 0;
}

int (*comparisonFunction)(struct Book *, struct Book *) = compareBooksByName;

void printUsage()
{
    return;
}

int checkInput(int argc, char *argv[])
{
    for (int i = 0; i < argc - 1; i++)
    {
        if (!strcmp(argv[i], "-i") ||
            !strcmp(argv[i], "--input"))
            return 1;
    }
    return 0;
}

void fastAddBook(int argc, char *argv[])
{

    FILE *inputFile = NULL;
    for (int i = 0; i < argc - 1; i++)
    {
        if (!strcmp(argv[i], "-i") ||
            !strcmp(argv[i], "--input"))
            inputFile = fopen(argv[i + 1], "r");
    }

    if (inputFile == NULL)
    {
        fprintf(stderr, "Could not open input file\n");
        return;
    }

    fclose(inputFile);

    return;
}

void boundBooks(struct Book *child, struct Book *parent, int side)
{

    if (parent != NULL)
    {
        if (side)
        {
            parent->larger = child;
        }
        else
        {
            parent->smaller = child;
        }
    }

    if (child != NULL)
        child->parent = parent;
}

int countLevel(struct Book *book)
{

    if (book == NULL)
        return 0;

    if (book->larger == NULL && book->smaller == NULL)
        return 1;
    int resultLarger = book->larger == NULL ? 0 : countLevel(book->larger);
    int resultSmaller = book->smaller == NULL ? 0 : countLevel(book->smaller);
    return resultLarger > resultSmaller ? resultLarger + 1 : resultSmaller + 1;
}

void balanceTree(struct Book *book)
{ // A

    int resultLarger = countLevel(book->larger);
    int resultSmaller = countLevel(book->smaller);

    if (abs(resultLarger - resultSmaller) < 2)
        return;

    struct Book *largerTree = resultLarger > resultSmaller ? // B
                                  book->larger
                                                           : book->smaller;

    int countLeft = countLevel(largerTree->smaller);
    int countRight = countLevel(largerTree->larger);

    if (resultLarger > resultSmaller)
    {
        if (countLeft < countRight)
        {
            struct Book *safeChild = largerTree->smaller;
            boundBooks(largerTree, book->parent,
                       comparisonFunction(book, book->parent) < 0 ? 0 : 1);
            boundBooks(safeChild, book, 1);
            boundBooks(book, largerTree, 0);
        }
        else if (countLeft > countRight)
        {
            // largerTree->smaller -- C
            struct Book *safeLeft = largerTree->smaller->smaller;
            struct Book *safeRight = largerTree->smaller->larger;

            boundBooks(largerTree->smaller, book->parent,
                       comparisonFunction(book, book->parent) < 0 ? 0 : 1);

            boundBooks(largerTree, largerTree->smaller, 1);
            boundBooks(book, largerTree->smaller, 0);

            boundBooks(safeLeft, book, 1);
            boundBooks(safeRight, largerTree, 0);
        }
    }
    else
    {
        if (countLeft > countRight)
        {
            struct Book *safeChild = largerTree->larger;
            boundBooks(largerTree, book->parent,
                       comparisonFunction(book, book->parent) < 0 ? 1 : 0);
            boundBooks(book, largerTree, 0);
            boundBooks(safeChild, book, 1);
        }
        else if (countLeft < countRight)
        {
            // largerTree->larger -- C
            struct Book *safeLeft = largerTree->larger->smaller;
            struct Book *safeRight = largerTree->larger->larger;

            boundBooks(largerTree->larger, book->parent,
                       comparisonFunction(book, book->parent) < 0 ? 1 : 0);

            boundBooks(largerTree, largerTree->larger, 0);
            boundBooks(book, largerTree->larger, 1);

            boundBooks(safeLeft, largerTree, 0);
            boundBooks(safeRight, book, 1);
        }
    }

    normiliseRoot();
}

void recursiveBalance(struct Book *book)
{

    if (book == NULL)
        return;

    balanceTree(book);
    recursiveBalance(book->smaller);
    recursiveBalance(book->larger);
}

void addBook(struct Book *book, struct Book **bookPlace)
{

    if (*bookPlace == NULL)
    {
        *bookPlace = book;
        globalBooksCounter += 1;
        return;
    }

    if (book == NULL)
        return;

    int result = comparisonFunction(book, *bookPlace);
    if (result > 0)
    {
        if ((*bookPlace)->larger == NULL)
            book->parent = *bookPlace;
        addBook(book, &((*bookPlace)->larger));
    }
    else if (result < 0)
    {
        if ((*bookPlace)->smaller == NULL)
            book->parent = *bookPlace;
        addBook(book, &((*bookPlace)->smaller));
    }
    else
    {
        printf("[Duplicate located: %s]\n", book->title);
    }

    balanceTree(*bookPlace);
}

struct Book *findBook(struct Book *book, struct Book *node)
{

    if (node == NULL)
        return NULL;

    int result = comparisonFunction(book, node);
    if (result > 0)
        return findBook(book, node->larger);
    else if (result < 0)
        return findBook(book, node->smaller);
    else
        return node;
}

void deleteBook(struct Book *book, struct Book *node)
{

    if (node == NULL)
        return;

    book = findBook(book, node);

    if (book == NULL)
        return;

    if (book->parent != NULL)
    {
        int result = comparisonFunction(book, book->parent);
        if (result > 0)
            book->parent->larger = NULL;
        else
            book->parent->smaller = NULL;
    }

    if (book->larger == NULL)
    {
        boundBooks(book->smaller, book->parent,
                   comparisonFunction(book->smaller, book->parent));
        if (book == books)
            books = book->smaller;
        free(book);
        globalBooksCounter -= 1;
        return;
    }

    boundBooks(book->larger, book->parent,
               comparisonFunction(book->larger, book->parent));
    addBook(book->larger->smaller, &(book->smaller));
    boundBooks(book->smaller, book->larger, 0);

    if (book == books)
        books = book->larger;

    if (node == books)
        globalBooksCounter -= 1;
    free(book);

    recursiveBalance(books);

    normiliseRoot();
}

void printHelp()
{
    printf("\tadd\t\t\t\t\tStart adding a book\n");
    printf("\tdelete ID\t\t\t\tDelete a book with the given ID\n");
    printf("\tedit ID\t\t\t\t\tEdit a book with the given ID\n");
    printf("\tsearch\t\t\t\t\tSearch for a book by the given data\n");
    printf("\tprint [sort field_type]\t\t\tPrint all the books in given order\n");
    printf("\tsave file\t\t\t\tSave all the data in a file\n");
    printf("\tload file\t\t\t\tLoad all the data from a file\n");
    return;
}

void resortBooks(char *fieldName)
{

    if (!strncmp(fieldName, "title", 5))
    {
        comparisonFunction = compareBooksByName;
    }
    else if (!strncmp(fieldName, "authors", 7))
    {
        comparisonFunction = compareBooksByAuthors;
    }
    else if (!strncmp(fieldName, "year", 4))
    {
        comparisonFunction = compareBooksByYear;
    }
    else if (!strncmp(fieldName, "distributor", 11))
    {
        comparisonFunction = compareBooksByDistributor;
    }
    else if (!strncmp(fieldName, "rate", 4))
    {
        comparisonFunction = compareBooksByRate;
    }
    else if (!strncmp(fieldName, "cost", 4))
    {
        comparisonFunction = compareBooksByCost;
    }
    else
    {
        return;
    }

    struct Book *oldRoot = books;
    books = NULL;

    int idCounterSave = globalIDCounter;

    while (oldRoot != NULL)
    {

        struct Book *book = createBook(oldRoot->title, oldRoot->authors, oldRoot->year,
                                       oldRoot->distributor, oldRoot->rate, oldRoot->cost);
        addBook(book, &books);
        book->ID = oldRoot->ID;
        struct Book *save;
        if (oldRoot->larger == NULL)
            save = oldRoot->smaller;
        else
            save = oldRoot->larger;
        deleteBook(oldRoot, oldRoot);
        oldRoot = save;
        if (oldRoot == NULL)
            continue;
        while (oldRoot->parent != NULL)
            oldRoot = oldRoot->parent;
        recursiveBalance(oldRoot);
    }

    globalIDCounter = idCounterSave;
}

void printBook(struct Book *book, FILE *stream)
{

    fprintf(stream, "Title: %s\n", book->title);
    fprintf(stream, "Author(s): %s\n", book->authors);
    fprintf(stream, "Year: %d\n", book->year);
    fprintf(stream, "distributor: %s\n", book->distributor);
    fprintf(stream, "Rate: %d\n", book->rate);
    fprintf(stream, "Cost: %d\n", book->cost);

    if (stream == stdout)
        fprintf(stream, "ID: %d\n\n", book->ID);
}

void searchInTitle(struct Book *book, char *data)
{

    if (book == NULL)
        return;

    searchInTitle(book->smaller, data);
    if (strstr(book->title, data) != NULL)
        printBook(book, stdout);
    searchInTitle(book->larger, data);
}

void searchInAuthors(struct Book *book, char *data)
{

    if (book == NULL)
        return;

    searchInAuthors(book->smaller, data);
    if (strstr(book->authors, data) != NULL)
        printBook(book, stdout);
    searchInAuthors(book->larger, data);
}

void searchInYear(struct Book *book, int data)
{

    if (book == NULL)
        return;

    searchInYear(book->smaller, data);
    if (book->year == data)
        printBook(book, stdout);
    searchInYear(book->larger, data);
}

void searchInDistributor(struct Book *book, char *data)
{

    if (book == NULL)
        return;

    searchInDistributor(book->smaller, data);
    if (strstr(book->distributor, data) != NULL)
        printBook(book, stdout);
    searchInDistributor(book->larger, data);
}

void searchInRate(struct Book *book, int data)
{

    if (book == NULL)
        return;

    searchInRate(book->smaller, data);
    if (book->rate == data)
        printBook(book, stdout);
    searchInRate(book->larger, data);
}

void searchInCost(struct Book *book, int data)
{

    if (book == NULL)
        return;

    searchInCost(book->smaller, data);
    if (book->cost == data)
        printBook(book, stdout);
    searchInCost(book->larger, data);
}

void searchBook()
{

    char *fieldName = (char *)malloc(sizeof(char) * 13);

    printf("Enter field name: ");
    fflush(stdout);
    fgets(fieldName, 12, stdin);
    fieldName[strlen(fieldName) - 1] = 0;

    printf("Enter data: ");
    fflush(stdout);

    if (!strncmp(fieldName, "title", 5))
    {
        char *data = (char *)malloc(sizeof(char) * (64 * 1024 * 1024 + 1));
        fgets(data, 64 * 1024 * 1024, stdin);
        data[strlen(data) - 1] = 0;

        searchInTitle(books, data);

        free(data);
    }
    else if (!strncmp(fieldName, "authors", 7))
    {
        char *data = (char *)malloc(sizeof(char) * (64 * 1024 * 1024 + 1));
        fgets(data, 64 * 1024 * 1024, stdin);
        data[strlen(data) - 1] = 0;

        searchInAuthors(books, data);

        free(data);
    }
    else if (!strncmp(fieldName, "year", 4))
    {
        int data;
        scanf("%d", &data);

        searchInYear(books, data);
        char c;
        while ((c = fgetc(stdin)) != EOF && (c != '\n'))
            ;
    }
    else if (!strncmp(fieldName, "distributo", 12))
    {
        char *data = (char *)malloc(sizeof(char) * (64 * 1024 * 1024 + 1));
        fgets(data, 10, stdin);
        fgets(data, 64 * 1024 * 1024, stdin);
        data[strlen(data) - 1] = 0;

        searchInDistributor(books, data);

        free(data);
    }
    else if (!strncmp(fieldName, "rate", 4))
    {
        int data;
        scanf("%d", &data);

        searchInRate(books, data);
        char c;
        while ((c = fgetc(stdin)) != EOF && (c != '\n'))
            ;
    }
    else if (!strncmp(fieldName, "cost", 4))
    {
        int data;
        scanf("%d", &data);

        searchInCost(books, data);
        char c;
        while ((c = fgetc(stdin)) != EOF && (c != '\n'))
            ;
    }

    free(fieldName);
}

struct Book *searchID(struct Book *book, int ID)
{

    if (book == NULL)
        return NULL;

    if (book->ID == ID)
        return book;
    struct Book *resultSmaller = searchID(book->smaller, ID);

    if (resultSmaller != NULL)
        return resultSmaller;

    return searchID(book->larger, ID);
}

void deleteID()
{

    printf("Print ID: ");
    fflush(stdout);

    int ID;
    scanf("%d", &ID);
    char c;
    while ((c = fgetc(stdin)) != EOF && (c != '\n'))
        ;

    struct Book *book = searchID(books, ID);
    if (book == NULL)
        printf("Could not find the book\n");
    else
        deleteBook(book, books);
}

void editID()
{

    printf("Print ID: ");
    fflush(stdout);

    int ID;
    scanf("%d", &ID);
    char c;
    while ((c = fgetc(stdin)) != EOF && (c != '\n'))
        ;

    struct Book *book = searchID(books, ID);
    if (book == NULL)
        printf("Could not find the book\n");
    else
    {
        char *buffer = (char *)malloc(sizeof(char) * (64 * 1024 * 1024 + 1));
        for (int i = 0; i < 6; i++)
        {

            switch (i)
            {
            case 0:
                printf("Title: ");
                break;
            case 1:
                printf("Author(s): ");
                break;
            case 2:
                printf("Year: ");
                break;
            case 3:
                printf("Distributor: ");
                break;
            case 4:
                printf("Rate: ");
                break;
            case 5:
                printf("Cost: ");
                break;
            }
            fflush(stdout);

            fgets(buffer, 64 * 1024 * 1024, stdin);
            buffer[strlen(buffer) - 1] = 0;
            printf("%s - %d\n", buffer, atoi(buffer));

            switch (i)
            {
            case 0:
                if (strlen(buffer) > 0)
                {
                    free(book->title);
                    book->title = (char *)malloc(sizeof(char) * strlen(buffer));
                    strncpy(book->title, buffer, strlen(buffer));
                }
                break;
            case 1:
                if (strlen(buffer) > 0)
                {
                    free(book->authors);
                    book->authors = (char *)malloc(sizeof(char) * strlen(buffer));
                    strncpy(book->authors, buffer, strlen(buffer));
                }
                break;
            case 2:
                if (atoi(buffer) != 0)
                    book->year = atoi(buffer);
                break;
            case 3:
                if (strlen(buffer) > 0)
                {
                    free(book->distributor);
                    book->distributor = (char *)malloc(sizeof(char) * strlen(buffer));
                    strncpy(book->distributor, buffer, strlen(buffer));
                }
                break;
            case 4:
                if (atoi(buffer) != 0)
                    book->rate = atoi(buffer);
                break;
            case 5:
                if (atoi(buffer) != 0)
                    book->cost = atoi(buffer);
                break;
            }
        }

    }
}

void loadFile(char *fileName)
{

    FILE *inputFile = fopen(fileName, "r");
    if (inputFile == NULL)
    {
        fprintf(stderr, "Could not open input file\n");
        return;
    }

    char *buffer = (char *)malloc(sizeof(char) * (64 * 1024 * 1024 + 1));

    while (!feof(inputFile))
    {
        char *title = NULL, *authors = NULL, *distributor = NULL;
        int rate = -1, year = -300, cost = -1;
        for (int i = 0; i < 6; i++)
        {

            fgets(buffer, 64 * 1024 * 1024, inputFile);
            buffer[strlen(buffer) - 1] = 0;

            if (feof(inputFile))
                break;

            switch (i)
            {
            case 0:
                title = (char *)malloc(sizeof(char) * strlen(buffer));
                strncpy(title, buffer, strlen(buffer));
                break;
            case 1:
                authors = (char *)malloc(sizeof(char) * strlen(buffer));
                strncpy(authors, buffer, strlen(buffer));
                break;
            case 2:
                year = atoi(buffer);
                break;
            case 3:
                distributor = (char *)malloc(sizeof(char) * strlen(buffer));
                strncpy(distributor, buffer, strlen(buffer));
                break;
            case 4:
                rate = atoi(buffer);
                break;
            case 5:
                cost = atoi(buffer);
                break;
            }
        }

        if (title == NULL || authors == NULL || distributor == NULL || rate == -1 || cost == -1 || year == -300)
            break;

        struct Book *newBook = createBook(title, authors, year, distributor, rate, cost);

        addBook(newBook, &books);
        printBook(newBook, stdout);
    }

    fclose(inputFile);
    free(buffer);

    return;
}

void writeBook(struct Book *book, FILE *outputFile)
{

    if (outputFile == NULL || book == NULL)
        return;

    fprintf(outputFile, "%s\n", book->title);
    fprintf(outputFile, "%s\n", book->authors);
    fprintf(outputFile, "%d\n", book->year);
    fprintf(outputFile, "%s\n", book->distributor);
    fprintf(outputFile, "%d\n", book->rate);
    fprintf(outputFile, "%d\n", book->cost);
}

void wanderTreeLUR(struct Book *book, FILE *stream, void (*func)(struct Book *, FILE *))
{

    if (book == NULL)
        return;

    wanderTreeLUR(book->smaller, stream, func);
    func(book, stream);
    wanderTreeLUR(book->larger, stream, func);
}

void wanderTreeRUL(struct Book *book, FILE *stream, void (*func)(struct Book *, FILE *))
{

    if (book == NULL)
        return;

    wanderTreeRUL(book->smaller, stream, func);
    func(book, stream);
    wanderTreeRUL(book->larger, stream, func);
}

void writeFile(char *fileName)
{

    FILE *outputFile = fopen(fileName, "w");
    if (outputFile == NULL)
    {
        fprintf(stderr, "Could not open output file\n");
        return;
    }

    wanderTreeLUR(books, outputFile, writeBook);

    fclose(outputFile);
}

void parseBook()
{

    char *buffer = (char *)malloc(sizeof(char) * (64 * 1024 * 1024 + 1));
    char *title, *authors, *distributor;
    int rate, cost, year;

    for (int i = 0; i < 6; i++)
    {

        switch (i)
        {
        case 0:
            printf("Title: ");
            break;
        case 1:
            printf("Author(s): ");
            break;
        case 2:
            printf("Year: ");
            break;
        case 3:
            printf("Distributor: ");
            break;
        case 4:
            printf("Rate: ");
            break;
        case 5:
            printf("Cost: ");
            break;
        }
        fflush(stdout);

        fgets(buffer, 64 * 1024 * 1024, stdin);
        buffer[strlen(buffer) - 1] = 0;

        switch (i)
        {
        case 0:
            title = (char *)malloc(sizeof(char) * strlen(buffer));
            strncpy(title, buffer, strlen(buffer));
            break;
        case 1:
            authors = (char *)malloc(sizeof(char) * strlen(buffer));
            strncpy(authors, buffer, strlen(buffer));
            break;
        case 2:
            year = atoi(buffer);
            break;
        case 3:
            distributor = (char *)malloc(sizeof(char) * strlen(buffer));
            strncpy(distributor, buffer, strlen(buffer));
            break;
        case 4:
            rate = atoi(buffer);
            break;
        case 5:
            cost = atoi(buffer);
            break;
        }
    }

    if (title == NULL || authors == NULL || distributor == NULL || rate == -1 || cost == -1 || year == -300)
        return;

    struct Book *newBook = createBook(title, authors, year, distributor, rate, cost);

    addBook(newBook, &books);

    printf("\nNEW ID IS -> %d\n", newBook->ID);
}

void enterInterectiveMode()
{

    printHelp();

    char command[65];

    while ("Ukrain does not exist")
    {

        printf("\n> ");
        fflush(stdout);
        fgets(command, 64, stdin);

        command[strlen(command) - 1] = 0;

        if (!strncmp(command, "load", 4))
        {
            if (strlen(command) < 6)
            {
                printHelp();
                continue;
            }
            char fileName[60];
            strncpy(fileName, command + 5, strlen(command) - 5);
            loadFile(fileName);
        }
        else if (!strncmp(command, "add", 3))
        {
            parseBook();
        }
        else if (!strncmp(command, "print", 5))
        {
            if (strlen(command) > 6)
            {
                char fieldName[12];
                strncpy(fieldName, command + 6, strlen(command) - 6);
                resortBooks(fieldName);
            }
            wanderTreeLUR(books, stdout, printBook);
        }
        else if (!strncmp(command, "save", 4))
        {
            if (strlen(command) < 6)
            {
                printHelp();
                continue;
            }
            char fileName[60];
            strncpy(fileName, command + 5, strlen(command) - 5);
            writeFile(fileName);
        }
        else if (!strncmp(command, "search", 6))
        {
            searchBook();
        }
        else if (!strncmp(command, "delete", 6))
        {
            deleteID();
        }
        else if (!strncmp(command, "edit", 4))
        {
            editID();
        }
        else
        {
            printHelp();
        }
    }
}

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        enterInterectiveMode();
        return 1;
    }

    if (!strcmp(argv[1], "-a") || !strcmp(argv[1], "--add"))
    {
        if (!checkInput(argc, argv))
        {
            printUsage();
            return 1;
        }
        fastAddBook(argc, argv);
    }

    return 0;
}
