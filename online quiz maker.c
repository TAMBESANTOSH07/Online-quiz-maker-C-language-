
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUIZZES 10
#define MAX_QUESTIONS 10

// Define structures for questions and quizzes
struct Question {
    char text[255];
    char options[4][100];
    int correctOption;
};

struct Quiz {
    char title[100];
    struct Question questions[MAX_QUESTIONS];
    int questionCount;
};

// Function to create a new question
struct Question createQuestion(char text[], char options[][100], int correctOption) {
    struct Question question;
    strcpy(question.text, text);
    for (int i = 0; i < 4; i++) {
        strcpy(question.options[i], options[i]);
    }
    question.correctOption = correctOption;
    return question;
}

// Function to create a new quiz
struct Quiz createQuiz(char title[]) {
    struct Quiz quiz;
    strcpy(quiz.title, title);
    quiz.questionCount = 0;
    return quiz;
}

// Function to add a question to a quiz
void addQuestionToQuiz(struct Quiz *quiz, struct Question question) {
    if (quiz->questionCount < MAX_QUESTIONS) {
        quiz->questions[quiz->questionCount] = question;
        quiz->questionCount++;
    } else {
        printf("Quiz is full. Cannot add more questions.\n");
    }
}

// Function to take a quiz
void takeQuiz(struct Quiz quiz) {
    int score = 0;
    printf("=== %s ===\n", quiz.title);
    for (int i = 0; i < quiz.questionCount; i++) {
        printf("Question %d: %s\n", i + 1, quiz.questions[i].text);
        for (int j = 0; j < 4; j++) {
            printf("%d. %s\n", j + 1, quiz.questions[i].options[j]);
        }
        int userAnswer;
        printf("Enter your answer (1-4): ");
        scanf("%d", &userAnswer);
        if (userAnswer == quiz.questions[i].correctOption) {
            printf("Correct!\n");
            score++;
        } else {
            printf("Incorrect. The correct answer is %d. \n", quiz.questions[i].correctOption);
        }
    }
    printf("Your score: %d out of %d\n", score, quiz.questionCount);
}

int main() {
    // Initialize an array to store quizzes
    struct Quiz quizzes[MAX_QUIZZES];
    int quizCount = 0;

    int choice;
    do {
        printf("Quiz Maker\n");
        printf("1. Create Quiz\n");
        printf("2. Take Quiz\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Create a new quiz
                if (quizCount < MAX_QUIZZES) {
                    char title[100];
                    printf("Enter quiz title: ");
                    scanf(" %[^\n]s", title);
                    struct Quiz quiz = createQuiz(title);
                    int questionCount;
                    printf("Enter the number of questions (1-%d): ", MAX_QUESTIONS);
                    scanf("%d", &questionCount);
                    for (int i = 0; i < questionCount; i++) {
                        char text[255];
                        char options[4][100];
                        int correctOption;
                        printf("Enter question text: ");
                        scanf(" %[^\n]s", text);
                        printf("Enter options:\n");
                        for (int j = 0; j < 4; j++) {
                            printf("Option %d: ", j + 1);
                            scanf(" %[^\n]s", options[j]);
                        }
                        printf("Enter the correct option (1-4): ");
                        scanf("%d", &correctOption);
                        struct Question question = createQuestion(text, options, correctOption);
                        addQuestionToQuiz(&quiz, question);
                    }
                    quizzes[quizCount] = quiz;
                    quizCount++;
                    printf("Quiz created and added to the list.\n");
                } else {
                    printf("Maximum number of quizzes reached. Cannot create more quizzes.\n");
                }
                break;
            case 2:
                // Take a quiz
                if (quizCount > 0) {
                    printf("Select a quiz to take:\n");
                    for (int i = 0; i < quizCount; i++) {
                        printf("%d. %s\n", i + 1, quizzes[i].title);
                    }
                    int selectedQuiz;
                    printf("Enter the number of the quiz you want to take: ");
                    scanf("%d", &selectedQuiz);
                    if (selectedQuiz >= 1 && selectedQuiz <= quizCount) {
                        takeQuiz(quizzes[selectedQuiz - 1]);
                    } else {
                        printf("Invalid quiz selection.\n");
                    }
                } else {
                    printf("No quizzes available to take.\n");
                }
                break;
            case 3:
                // Exit the program
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 3);

    return 0;
}