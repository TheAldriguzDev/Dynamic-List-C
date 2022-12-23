#include <stdio.h>
#include <stdlib.h>

/*
 
 printf(" $$$$$$\  $$\       $$\           $$\                               \n");
 printf("$$  __$$\ $$ |      $$ |          \__|                              \n");
 printf("$$ /  $$ |$$ | $$$$$$$ | $$$$$$\  $$\  $$$$$$\  $$\   $$\ $$$$$$$$\ \n");
 printf("$$$$$$$$ |$$ |$$  __$$ |$$  __$$\ $$ |$$  __$$\ $$ |  $$ |\____$$  |\n");
 printf("$$  __$$ |$$ |$$ /  $$ |$$ |  \__|$$ |$$ /  $$ |$$ |  $$ |  $$$$ _/ \n");
 printf("$$ |  $$ |$$ |$$ |  $$ |$$ |      $$ |$$ |  $$ |$$ |  $$ | $$  _/   \n");
 printf("$$ |  $$ |$$ |\$$$$$$$ |$$ |      $$ |\$$$$$$$ |\$$$$$$  |$$$$$$$$\ \n");
 printf("\__|  \__|\__| \_______|\__|      \__| \____$$ | \______/ \________|\n");
 printf("                                      $$\   $$ |                    \n");
 printf("                                      \$$$$$$  |                    \n");
 
 Liste dinamiche in ansi-C
 
 Ricordiamo che con:
 * --> accediamo al dato contenuto dall'indirizzo puntato
 & --> prendiamo l'indirizzo di memoria in cui è contenuta una certa variabile
 
 Nelle funzioni: "pushItem", "insertInPosition", "deleteItem" utilizziamo un cursore per non
 modificare la testa della nostra lista. Si potrebbe anche fare senza per ottimizzare il codice,
 in un modo leggermente diverso.
 
 
 */

// definiamo la struttura:
struct node{
    int data;
    struct node* next;
};

// creiamo un tipo nodo
typedef struct node Node;

// creiamo un tipo puntatore a lista
typedef Node *node_pointer;

// Funzione che printa tutti i valori della Lista
void logList(node_pointer List){
    // controlliamo se la lista è vuota
    if (List == NULL){
        printf("The list is empty. I can't log any values!\n");
        return;
    } else {
        // scorriamo tutti gli elementi della lista e li printiamo
        while (List != NULL) {
            printf("[%d] ", List->data);
            List = List->next;
        }
        printf("\n");
    }
}

// Funzione che tramite la ricorsione inverte la lista, dopo la chiamata alla funzione dovremo anche fare un printf("\n") per andare a capo
void logListInvert(node_pointer List){
    if (List == NULL){
        printf("The list is empty. I can't log any values!\n");
        return;
    } else {
        if (List->next != NULL){
            logListInvert(List->next);
            printf("[%d] ", List->data);
        } else {
            printf("[%d] ", List->data);
        }
    }
}

// Funzione che ritorna il valore dell'elemento se trovato, altrimenti ritorna -1
int indexOf(node_pointer List, int element){
    // controlliamo se la List è vuota
    if (List == NULL){
        printf("The list is empty, the element is not into the List!\n");
        return -1;
    } else {
        // scorriamo tutta la lista
        while (List != NULL) {
            // cerchiamo nella lista l'elemento desiderato
            if (List->data == element){
                return element;
            }
            List = List->next;
        }
        return -1;
    }
}

// Funzione che inserisce un nuovo elemento in testa alla lista
void insertFront(node_pointer *List, int element){
    // Inizializzazione del nuovo nodo e malloc
    node_pointer newNode = NULL;
    newNode = (node_pointer)malloc(sizeof(node_pointer));
    if (newNode == NULL){
        printf("Out of memory!\n");
        return;
    } else {
        // assegnamenti al nuovo nodo
        newNode->data = element;
        newNode->next = *List;
        
        // Cambio della testa
        *List = newNode;
    }
}

// Funzione che inserisce un nuovo elemento alla fine della lista
void pushItem(node_pointer *List, int element){
    /*
     Inizializzione del:
     - nuovo nodo
     - cursore che useremo per spostarci all'interno della lista senza dover spostare la testa della nostra lista
     */
    node_pointer newNode = NULL;
    node_pointer cursor = *List;
    
    newNode = (node_pointer)malloc(sizeof(node_pointer));
    if (newNode == NULL){
        printf("Out of memory!\n");
        return;
    } else {
        newNode->data = element;
        // caso lista vuota
        if (*List == NULL){
            // insertFront(List, element); potremmo anche ragionare in questo modo
            newNode->next = *List; // in questo caso *List = NULL per inizializziane nel main
            
            *List = newNode;
        } else {
            // scorriamo la lista e ci fermiamo all'ultimo elemento
            while (cursor->next != NULL){
                cursor = cursor->next;
            }
            // il nuovo nodo punta a NULL, infatti è l'ultimo elemento
            newNode->next = NULL;
            
            // aggiorniamo il valore a cui punta l'ultimo elemento al nuovo nodo creato
            cursor->next = newNode;
        }
    }
}

// Funzione che inserisce in una data posizione il nuovo elemento
void insertInPosition(node_pointer *List, int element, int pos){
    node_pointer newNode = NULL;
    node_pointer prevElem = NULL;
    node_pointer cursor = *List;
    int i = 0;
    
    // controlliamo la posizione data dall'utente
    if (pos < 0){
        printf("The given position is not correct!\n");
        return;
    } else {
        newNode = (node_pointer)malloc(sizeof(node_pointer));
        if (newNode == NULL){
            printf("Out of memory!\n");
            return;
        } else {
            // caso posizione uguale a 0 --> inserimento in testa
            newNode->data = element;
            if (pos == 0){
                newNode->next = *List; // assegniamo il valore a cui punta il nostro nuovo nodo, può essere NULL o un nuovo nodo
                
                *List = newNode; // aggiorniamo la testa
            } else {
                // scorriamo ora tutta la lista fino a quando troviamo la pos o la lista finisce
                while (i != pos && cursor != NULL){
                    prevElem = cursor;
                    cursor = cursor->next;
                    i++;
                }
                /*
                 Se questo controllo non viene fatto, l'elemento verrebbe inserito nell'ultima posizione, e non nella posizione inserita dall'utente
                */
                if (i < pos){
                    printf("List index out of range!\n");
                    return;
                } else {
                    // aggiorniamo ora i valori a cui puntano i vari elementi
                    newNode->next = cursor;
                    prevElem->next = newNode;
                }
            }
        }
    }
}

// Funzione che cancella un elemento ricercandolo all'interno della lista. Ritorna -1 se c'è stato un errore
int deleteElement(node_pointer *List, int element){
    node_pointer cursor = *List;
    node_pointer prevElem = NULL; // salviamo elemento precedente
    node_pointer nextElem = NULL; // salviamo elemento successivo
    int deletedElem; // valore che ritorniamo se cancelliamo l'elemento
    
    // caso lista vuota
    if (*List == NULL){
        printf("The list is empty! I can't delete the element!\n");
        return -1;
    } else {
        // caso elemento da cancellare è nella testa della lista
        if (cursor != NULL && cursor->data == element){
            deletedElem = cursor->data;
            *List = cursor->next;
            free(cursor);
            return deletedElem;
        } else {
            // scorro la lista fino a quando non incontro l'elemento da cancellare
            while (cursor != NULL && cursor->data != element){
                prevElem = cursor; // salvo il precedente
                cursor = cursor->next; // aggiorno il cursore
                nextElem = cursor->next; // salvo il successivo
            }
            /*
             Controllo se siamo arrivati alla fine della lista:
             - se si --> allora non abbiamo trovato l'elemento
             - se no --> abbiamo trovato l'elemento
             */
            if (cursor == NULL){
                printf("The selected element is not in the list!\n");
                return -1;
            } else {
                deletedElem = cursor->data; // salvo il valore da ritornare
                prevElem->next = nextElem; // aggiorno il valore a cui punta il prev
                free(cursor); // libero la memoria
                return deletedElem;
            }
        }
    }
}

int main() {
    // inizializziamo la testa a NULL
    node_pointer head = NULL;

    insertFront(&head, 1);
    insertFront(&head, 3);
    insertFront(&head, 6);
    insertFront(&head, 4);
    pushItem(&head, 98);
    pushItem(&head, 1902);
    insertInPosition(&head, 988, 4);

    logList(head);
    //logListInvert(head);
    //printf("\n");
    
    int searchElem = 8;
    if (indexOf(head, searchElem) != -1){
        printf("Elem: %d has been found in the List\n", searchElem);
    } else {
        printf("Elem: %d not found int the List\n", searchElem);
    }
    
    if (deleteElement(&head, 1) != -1){
        printf("Element has been deleted!\n");
        logList(head);
    } else {
        printf("Error while deleting the element in the list!\n");
    }
    
    return 0;
}
