#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Book {
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


struct Book *createBook(char *title, char *authors, int year, char *distributor, int rate, int cost) {
    struct Book *newBook = (struct Book *)malloc(sizeof(struct Book));

    if (newBook == NULL) {
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

void normiliseRoot() {
    while (books->parent != NULL)
        books = books->parent;
}

int compareBooksByName(struct Book *first, struct Book *second) {

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

int compareBooksByAuthor(struct Book *first, struct Book *second) {

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

int compareBooksByYear(struct Book *first, struct Book *second) {

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

int compareBooksByDistributor(struct Book *first, struct Book *second) {

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

int compareBooksByRate(struct Book *first, struct Book *second) {

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

int compareBooksByCost(struct Book *first, struct Book *second) {

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


void printUsage() {
    return ;
}

int checkInput(int argc, char *argv[]) {
    for (int i = 0; i < argc - 1; i++) {
        if (!strcmp(argv[i], "-i") ||
                !strcmp(argv[i], "--input"))
            return 1;
    }
    return 0;
}

void fastAddBook(int argc, char *argv[]) {

    FILE *inputFile = NULL;
	for (int i = 0; i < argc - 1; i++) {
        if (!strcmp(argv[i], "-i") ||
                !strcmp(argv[i], "--input"))
            inputFile = fopen(argv[i + 1], "r");
    }

    if (inputFile == NULL) {
        fprintf(stderr, "Could not open input file\n");
        return;
    }



    fclose(inputFile);

    return;
}



void boundBooks(struct Book *child, struct Book *parent, int side) {
    
    if (parent != NULL) {
        if (side) {
            parent->larger = child;
        } else {
            parent->smaller = child;
        }
    }

    if (child != NULL)
        child->parent = parent;

}

int countLevel(struct Book *book) {

    if (book == NULL)
        return 0;

    if (book->larger == NULL && book->smaller == NULL)
        return 1;
    int resultLarger = book->larger == NULL ? 0 : countLevel(book->larger);
    int resultSmaller = book->smaller == NULL ? 0 : countLevel(book->smaller);
    return resultLarger > resultSmaller ? resultLarger + 1 : resultSmaller + 1;

}

void balanceTree(struct Book *book) { // A

    int resultLarger = countLevel(book->larger);
    int resultSmaller = countLevel(book->smaller);

    if (abs(resultLarger - resultSmaller) < 2)
        return;
    
    struct Book *largerTree = resultLarger > resultSmaller ? // B
            book->larger : book->smaller;

    int countLeft = countLevel(largerTree->smaller);
    int countRight = countLevel(largerTree->larger);

    if (resultLarger > resultSmaller) {
        if (countLeft < countRight) {
            struct Book *safeChild = largerTree->smaller;
            boundBooks(largerTree, book->parent,
                    comparisonFunction(book, book->parent) < 0 ? 0 : 1);
            boundBooks(safeChild, book, 1);
            boundBooks(book, largerTree, 0);
        } else if (countLeft > countRight) {
            // largerTree->larger -- C
            struct Book *safeLeft = largerTree->larger->smaller;
            struct Book *safeRight = largerTree->larger->larger;

            boundBooks(largerTree->larger, book->parent,
                    comparisonFunction(book, book->parent) < 0 ? 0 : 1);

            boundBooks(largerTree, largerTree->larger, 1);
            boundBooks(book, largerTree->larger, 0);

            boundBooks(safeLeft, book, 1);
            boundBooks(safeRight, largerTree, 0);
        }
    } else {
        if (countLeft > countRight) {
            struct Book *safeChild = largerTree->larger;
            boundBooks(largerTree, book->parent,
                    comparisonFunction(book, book->parent) < 0 ? 1 : 0);
            boundBooks(book, largerTree, 0);
            boundBooks(safeChild, book, 1);
        } else if (countLeft < countRight) {
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

void recursiveBalance(struct Book *book) {

    if (book == NULL)
        return;
    
    balanceTree(book);
    recursiveBalance(book->smaller);
    recursiveBalance(book->larger);

}

void addBook(struct Book *book, struct Book **bookPlace) {

    if (*bookPlace == NULL) {
        *bookPlace = book;
        globalBooksCounter += 1;
        return;
    }

    if (book == NULL)
        return;

    int result = comparisonFunction(book, *bookPlace);
    if (result > 0) {
        if ((*bookPlace)->larger == NULL)
            book->parent = *bookPlace;
        addBook(book, &((*bookPlace)->larger));
    } else if (result < 0) {
        if ((*bookPlace)->smaller == NULL)
            book->parent = *bookPlace;
        addBook(book, &((*bookPlace)->smaller));
    } else {
        printf("[Duplicate located: %s]\n", book->title);
    }

    balanceTree(*bookPlace);

}

struct Book *findBook(struct Book *book, struct Book *node) {

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

void deleteBook(struct Book *book, struct Book *node) {

    if (node == NULL)
        return;
    
    book = findBook(book, node);
    
    if (book == NULL)
        return;
    
    if (book->parent != NULL) {
        int result = comparisonFunction(book, book->parent);
        if (result > 0)
            book->parent->larger = NULL;
        else
            book->parent->smaller = NULL;
    }

    if (book->larger == NULL) {
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

    free(book);
    globalBooksCounter -= 1;

    recursiveBalance(books);

    normiliseRoot();

}

void printHelp() {
    printf("\tadd\t\t\t\t\tStart adding a book\n");
    printf("\tdelete ID\t\t\t\tDelete a book with the given ID\n");
    printf("\tedit ID\t\t\t\t\tEdit a book with the given ID\n");
    printf("\tsearch field_type data\t\t\tSearch for a book by the given data\n");
    printf("\tprint [sort field type up/down]\t\tPrint all the books in given order\n");
    printf("\tsave file\t\t\t\tSave all the data in a file\n");
    printf("\tload file\t\t\t\tLoad all the data from a file\n");
    return;
}

void printBook(struct Book *book) {
    printf("Title: %s\n", book->title);
    printf("Author(s): %s\n", book->authors);
    printf("Year: %d\n", book->year);
    printf("distributor: %s\n", book->distributor);
    printf("Rate: %d\n", book->rate);
    printf("Cost: %d\n", book->cost);
}

void loadFile(char *fileName) {

    FILE *inputFile = fopen(fileName, "r");
    if (inputFile == NULL) {
        fprintf(stderr, "Could not open input file\n");
        return;
    }

    char *buffer = (char *)malloc(sizeof(char) * (64 * 1024 * 1024 + 1));

    while (!feof(inputFile)) {
        char *title = NULL, *authors = NULL, *distributor = NULL;
        int rate = -1, year = -300, cost = -1;
        for (int i = 0; i < 6; i++) {

            fgets(buffer, 64 * 1024 * 1024, inputFile);
            buffer[strlen(buffer) - 1] = 0;

            if (feof(inputFile))
                break;

            switch (i) {
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

        if (title == NULL || authors == NULL || distributor == NULL \
                || rate == -1 || cost == -1 || year == -300)
            break;
        
        struct Book *newBook = createBook(title, authors, year, distributor, rate, cost);

        addBook(newBook, &books);
        printBook(newBook);
    }

    fclose(inputFile);

    return;
}

void enterInterectiveMode() {

    printHelp();

    char command[65];

    while ("Ukrain does not exist") {

        printf("\n> ");
        fflush(stdout);
        fgets(command, 64, stdin);

        command[strlen(command) - 1] = 0;

        if (!strncmp(command, "load", 4)) {
            if (strlen(command) < 6) {
                printHelp();
                continue;
            }
            char fileName[60];
            strncpy(fileName, command + 5, strlen(command) - 5);
            loadFile(fileName);
        } else if (!strncmp(command, "add", 3)) {
            printHelp();
        } else {
            printHelp();
        }

    }

}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        enterInterectiveMode();
        return 1;
    }

    if (!strcmp(argv[1], "-a") || !strcmp(argv[1], "--add")) {
        if (!checkInput(argc, argv)) {
        	printUsage();
        	return 1;
        }
        fastAddBook(argc, argv);
    }

    return 0;
}
