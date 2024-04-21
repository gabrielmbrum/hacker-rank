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

struct document get_document(char* text) {
    struct document doc;
    int par_count = 0, sen_count = 0, wor_count = 0, w_lenght = 0;

    for (int i = 0; text[i] != NULL; i++) 
        if ((int)text[i] == 92 && text[i+1] == 'n') par_count++;   // '(int)text[i] == 92' confere se text[i] = '\' 

    doc.paragraph_count = par_count;
    doc.data = (struct paragraph*) malloc(sizeof(struct paragraph) * par_count);

    for (int i = 0; i < par_count; i++) {
        // create all paragraphs
        struct paragraph newParagraph;

        for (int j = i; (int)text[i] != 92 || text[i+1] != 'n'; j++)
            if (text[j] == '.') sen_count++;

        newParagraph.sentence_count = sen_count;
        newParagraph.data = (struct sentence*) malloc(sizeof(struct sentence) * sen_count);

        for (int j = i; (int)text[i] != 92 || text[i+1] != 'n'; j++) {
            // create all sentences
            struct sentence newSen;
            
            for (int k = j; text[k] != '.'; k++)
                if (text[k] == ' ') wor_count++;

            newSen.word_count = wor_count;
            newSen.data = (struct word*) malloc(sizeof(struct word) * wor_count+1);

            for (int k = j; text[k] != '.'; k++) {
                // create all words
                struct word newWord;

                for (int l = k; text[l] != ' ' || text[l] != '.'; l++)
                    w_lenght++;
                
                newWord.data = (char*) malloc(sizeof(char) * w_lenght);

                for (int l = k; text[l]  != ' ' || text[l] != '.'; l++) 
                    newWord.data[l] = text[l];

                newSen.data[k] = newWord;
            }

            newParagraph.data[j] = newSen;
        }

        doc.data[i] = newParagraph;
    }

    return doc;
}

struct word kth_word_in_mth_sentence_of_nth_paragraph(struct document Doc, int k, int m, int n) {
    print_word(Doc.data[n].data[m].data[k]);
}

struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k, int m) { 
    print_sentence(Doc.data[m].data[k]);
}

struct paragraph kth_paragraph(struct document Doc, int k) {
    print_paragraph(Doc.data[k]);
}

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
    scanf("%d", &q);

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
            struct sentence sen= kth_sentence_in_mth_paragraph(Doc, k, m);
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