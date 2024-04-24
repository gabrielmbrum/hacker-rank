#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5


struct word {
    char* data;
};

struct sentence {
    struct word* data;
    int word_count;//denotes number of words in a sentence
};

struct paragraph {
    struct sentence* data  ;
    int sentence_count;//denotes number of sentences in a paragraph
};

struct document {
    struct paragraph* data;
    int paragraph_count;//denotes number of paragraphs in a document
};

void print_word(struct word w);

void print_word(struct word w) {
    printf("%s", w.data);
}

void print_sentence(struct sentence sen) {
    for(int i = 0; i < sen.word_count; i++) {
        print_word(sen.data[i]);
        if (i != sen.word_count - 1) {
            printf(" ");
        }
    }
}

void print_paragraph(struct paragraph para) {
    for(int i = 0; i < para.sentence_count; i++){
        print_sentence(para.data[i]);
        printf(".");
    }
}

void print_document(struct document doc) {
    for(int i = 0; i < doc.paragraph_count; i++) {
        print_paragraph(doc.data[i]);
        if (i != doc.paragraph_count - 1)
            printf("\n");
    }
}

struct document get_document(char* text) {
    struct document doc;
    int par_count = 0, sen_count = 0, wor_count = 0, w_lenght = 0, index = 0, i;

    for (i = 0; text[i] != '\0'; i++) 
        if (text[i] == '\n') par_count++;
    par_count++;

    doc.paragraph_count = par_count;
    doc.data = (struct paragraph*) malloc(sizeof(struct paragraph) * par_count);
    
    for (i = 0; i < par_count; i++) {
        // inserting in document all its paragraphs
        struct paragraph newParagraph;
        int j = index;
        for (; text[j] != '\n' && text[j] != '\0'; j++)
            if (text[j] == '.') sen_count++;

        newParagraph.sentence_count = sen_count;
        newParagraph.data = (struct sentence*) malloc(sizeof(struct sentence) * sen_count);
        

        for (int j = 0; j < sen_count; j++) { // j count the sentences
            // inserting in paragraph all its sentences
            struct sentence newSen;
            
            for (int k = index; text[k] != '.'; k++)
                if (text[k] == ' ') {wor_count++;}
            wor_count++;

            newSen.word_count = wor_count;
            newSen.data = (struct word*) malloc(sizeof(struct word) * wor_count);

            
            for (int k = 0; k < wor_count; k++) { // k count the words
                // inserting in sentences all its words
                struct word newWord;

                for (int l = index; text[l] != ' ' && text[l] != '.'; l++)
                    w_lenght++;
                
                newWord.data = (char*) malloc(sizeof(char) * w_lenght);
                
                for (int l = index, m = 0; text[l]  != ' ' && text[l] != '.'; l++, m++) {
                    newWord.data[m] = text[l];
                }
                
                newSen.data[k] = newWord;
                index += w_lenght;
                w_lenght = 0;
                if (text[index] == '.') {index += 2;}
                if (text[index] == ' ') { index++;}
            }
            newParagraph.data[j] = newSen;
            wor_count = 0;
        }
        doc.data[i] = newParagraph;
        sen_count = 0;
    }
    return doc;
}

struct word kth_word_in_mth_sentence_of_nth_paragraph(struct document Doc, int k, int m, int n) {
    struct word* word_ret = &Doc.data[k - 1].data[m-1].data[n-1];
    return *word_ret;
}

struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k, int m) { 
    struct sentence* sentence_ret = &Doc.data[k - 1].data[m-1];
    return *sentence_ret;
}

struct paragraph kth_paragraph(struct document Doc, int k) {
    struct paragraph* paragraph_ptr = &Doc.data[k - 1];
    return *paragraph_ptr;
}

char* get_input_text() {	
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1) //it's not the last paragraph
            strcat(doc, "\n");
    }

    char* returnDoc = (char*) malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

int main() 
{
    char* text = get_input_text();
    struct document Doc = get_document(text);
    int q;
    scanf("%d", &q); //quantify of operations

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            struct word w = kth_word_in_mth_sentence_of_nth_paragraph(Doc, k, m, n);
            print_word(w);
        }

        else if (type == 2) {
            int k, m;
            scanf("%d %d", &k, &m);
            struct sentence sen = kth_sentence_in_mth_paragraph(Doc, k, m);
            print_sentence(sen);
        }

        else{
            int k;
            scanf("%d", &k);
            struct paragraph para = kth_paragraph(Doc, k);
            print_paragraph(para);
        }
        printf("\n");
    }     
    
}