class Book{
    int book_id;
    static int libSize;
    string book_name, author_name;
    Book *head, *prev, *next;

public:
    Book(){
        head = 0;
    }
    void Add(int, int, string, string);
    void Delete(int, int, string, string);
    void Insert(int, string, string);
    void Sort(int);
    // bool isEmpty();
    bool Search(int);
    void PrintBook(string);
};

void Book::Add(int pos, int id, string name, string author){
    Book *temp = new Book;
    temp->book_id = id;
    temp->book_name = name;
    temp->author_name = author;

    // place book at top
    if (pos == 0){
        temp->next = head;
        head = temp;
        head->prev = nullptr;
        libSize++;
    }
    // place book at bottom
    else if ( pos >=  libSize ) {
        temp->next = nullptr;
        Book * current = head;
        
        while (current->next != nullptr) {
            current = current->next;
        }
        
        current->next = temp;
        temp->prev = current;
        libSize++;
    }
    //place book at random position
    else if (pos >= 1 && pos < libSize ){
        
        Book *current = head;
        Book *previous = current;
        int counter = 0;

        while (counter != pos) {
            previous = current;
            current = current->next;
            counter++;
        }

        temp->next = current;
        temp->prev = current->prev;
        previous->next = temp;
        current->prev = temp;
        libSize++;
    }
}

void Book::Delete(int pos, int id, string name, string author){
    // remove book according to position
    if(pos >= 0 && pos <= libSize ){
    	// remove book from top
        if (pos == 0){
            Book * current = head;
            head = current->next;
            head->prev = 0;
            delete current;
            libSize--;
        }
        // remove book from other places
        else{
            Book * current = head;
            Book * previous = current;
            int counter = 0;
            
            while (counter != pos) {
                previous = current;
                current = current->next;
                counter++;
            }

            previous->next = current->next;
            current->next->prev = previous;
            delete current;
            libSize--;
        }
    }
    // remove book according to ID
    else if(id != -1){
        Book *temp = head;
        Book *prev = new Book;

        while (temp != NULL && temp->book_id == id){
            temp = head->next;
            delete head;
            head = temp;
            libSize--;
        }
        while (temp != NULL){
            while (temp != NULL && temp->book_id != id){
                prev = temp;
                temp = temp->next;
            }
            if (temp == NULL) return;
            prev->next = temp->next;
            delete temp;
            temp = prev->next;
            libSize--;
        }
    }
    // remove book according to Name
    else if(name != ""){
        Book *temp = head;
        Book *prev = new Book;
        while (temp != NULL && temp->book_name == name){
            temp = head->next;
            delete head;
            head = temp;
            libSize--;
        }
        while (temp != NULL){
            while (temp != NULL && temp->book_name != name){
                prev = temp;
                temp = temp->next;
            }
            if (temp == NULL) return;
            prev->next = temp->next;
            delete temp;
            temp = prev->next;
            libSize--;
        }
    }
    // remove book according to author
    else if(author != ""){
        Book *temp = head;
        Book *prev = new Book;

        while (temp != NULL && temp->author_name == author){
            temp = head->next;
            delete head;
            libSize--;
            head = temp;
        }

        while (temp != NULL){        {
        	cout<<777<<temp->author_name<<author<<endl;
            while (temp != NULL && temp->author_name != author){
                prev = temp;
                temp = temp->next;
            }
            if (temp == NULL) return;
            prev->next = temp->next;
            delete temp;
            temp = prev->next;
            libSize--;
        }
    }
}

//Insert into the Book List
void Book::Insert(int id, string name, string author){
    Book *temp = new Book;
    temp->book_id = id;
    temp->book_name = name;
    temp->author_name = author;
    
    if (head == 0){
        temp->next = head;
        head = temp;
        head->next = nullptr;
        libSize++;
    }else{
        temp->next = nullptr;
        Book * current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = temp;
        temp->prev = current;
        libSize++;
    }
}

void Book::Sort(int sortby){
    switch(sortby){
        case 1:{
            if (head != 0)
            {
                Book* current = head;
                Book* prev = 0;
                Book* tempNode = 0;
                int changeFlag = 0;

                for (int i = 0; i < libSize; i++)
                {
                    while (current->next != nullptr)
                    {
                        tempNode = current->next;
                        
                        if (current->book_id > tempNode->book_id)
                        {
                            changeFlag = 1;
                            current->next = tempNode->next;
                            tempNode->next = current;
                            if (prev != 0)
                                prev->next = tempNode;
                            prev = tempNode;
                            if (head == current)
                                head = tempNode;
                        }
                        else
                        {
                            prev = current;
                            current = current->next;
                        }
                    }
                    if (changeFlag == 0)
                        break;
                    else
                    {
                        prev = 0;
                        current = head;
                        changeFlag = 0;
                    }
                }
            }
        }
        case 2:{
            if (head != 0)
            {
                Book* current = head;
                Book* prev = 0;
                Book* tempNode = 0;
                int changeFlag = 0;
                for (int i = 0; i < libSize; i++)
                {
                    while (current->next != nullptr)
                    {
                        tempNode = current->next;
                        
                        if (int(current->book_name[0])> int(tempNode->book_name[0]))
                        {
                            changeFlag = 1;
                            current->next = tempNode->next;
                            tempNode->next = current;
                            if (prev != 0)
                                prev->next = tempNode;
                            prev = tempNode;
                            if (head == current)
                                head = tempNode;
                        }
                        else
                        {
                            prev = current;
                            current = current->next;
                        }
                    }
                    if (changeFlag == 0)
                        break;
                    else
                    {
                        prev = 0;
                        current = head;
                        changeFlag = 0;
                    }
                }
            }
        }
        case 3:{
            if (head != 0)
            {
                Book* current = head;
                Book* prev = 0;
                Book* tempNode = 0;
                int changeFlag = 0;
                for (int i = 0; i < libSize; i++)
                {
                    while (current->next != nullptr)
                    {
                        tempNode = current->next;
                        
                         if (int(current->author_name[0])> int(tempNode->author_name[0]))
                        {
                            changeFlag = 1;
                            current->next = tempNode->next;
                            tempNode->next = current;
                            if (prev != 0)
                                prev->next = tempNode;
                            prev = tempNode;
                            if (head == current)
                                head = tempNode;
                        }
                        else
                        {
                            prev = current;
                            current = current->next;
                        }
                    }
                    if (changeFlag == 0)
                        break;
                    else
                    {
                        prev = 0;
                        current = head;
                        changeFlag = 0;
                    }
                }
            }
        }
        default:{
            
        }
    }
}

bool Book::Search(int id){
    if (head != 0){
        Book * temp = head;
        while(temp != NULL ){
            if (temp->book_id == id){
                return true;
            }
             temp = temp->next;
        }
        return false;
    }
    return false;
}

//Print Book to the output file
void Book::PrintBook(string outfilename){
    ofstream outfile;
    outfile.open(outfilename);
    Book * temp = head;
    if (outfile.is_open())
    {
        while(temp != NULL){
            outfile<<"book_id"<<":"<<temp->book_id<<", "<<"book_name"<<":"<< temp->book_name<< ", "<<"book_author"<<":"<<temp->author_name<<endl;
            temp = temp->next;
        }
    }
    outfile.close();
}