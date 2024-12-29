#include "JSONlang.h"
#define KEY(key) std::string(#key)
#define OBJECT//{...} JsonObject{std::initializer_list<std::pair<std::string, std::shared_ptr<JsonValue>>>{__VA_ARGS__}}
#define ARRAY//{...} JsonArray{std::initializer_list<std::shared_ptr<JsonValue>>{__VA_ARGS__}}
int main() {

    JSON(emptyObj) = OBJECT{};
    JSON(emptyArray) = ARRAY{};
    // Orismos enos keno antikeimenou
    //JSON(emptyObj) = OBJECT{};
    // Orismos enos keno pinaka
    //JSON(emptyArray) = ARRAY{};

    // Orismos enos arithmou
    JSON(someNumber) = NUMBER(42);

    // Orismos timon true kai false
    JSON(isTrue) = TRUE;
    JSON(isFalse) = FALSE;

    // Orismos mias null timis
    JSON(nothing) = null;

    // Orismos enos vivliou me enthesa antikeimena kai pinakes
    JSON(book) = OBJECT{
            {KEY("title"),        STRING("Gone Girl")},
            {KEY("published"),    NUMBER(2012)},
            {KEY("type"),         STRING("Thriller")},
            {KEY("author"), OBJECT{
                                          {KEY("firstname"), STRING("GILLIAN")},
                                          {KEY("sirname"), STRING("FLYNN")},
                                          {KEY("age"), NUMBER(45)},
                                          {KEY("books_written"), ARRAY{
                                                                              STRING("Sharp Objects"),
                                                                              STRING("Dark Places")
                                                                      }}
                                  }},
            {KEY("genres"), ARRAY {
                                          STRING("Fiction"),
                                          STRING("Thriller"),
                                          STRING("Crime")
                                  }}
    };

    // Orismos pinaka thermokrasion gia mia evdomada
    JSON(week_temperatures) = ARRAY[
            NUMBER(20), NUMBER(19.5), NUMBER(19), NUMBER(20),
            NUMBER(19), NUMBER(18.5), NUMBER(19)
    ];

    // Orismos enos poliplokou antikeimenou me enthesa antikeimena kai pinakes gia mathites
    JSON(students) = ARRAY{
            OBJECT{
                    {KEY("name"), STRING("Nikos Nikolaou")},
                    {KEY("id"), NUMBER(4444)},
                    {KEY("grades"), ARRAY{
                            OBJECT{
                                    {KEY("subject"), STRING("hy100")},
                                    {KEY("grade"), NUMBER(7.5)}
                            },
                            OBJECT{
                                    {KEY("subject"), STRING("hy150")},
                                    {KEY("grade"), NUMBER(8)}
                            }
                    }},
                    {KEY("courses"), ARRAY{
                            STRING("CS101"),
                            STRING("CS102")
                    }}
            },
            OBJECT{
                    {KEY("name"), STRING("Maria Papadopoulou")},
                    {KEY("id"), NUMBER(4445)},
                    {
                            KEY("grades"), ARRAY{
                            OBJECT{
                                { KEY("subject"), STRING("hy100") },
                                { KEY("grade"), NUMBER(6) }
                            },
                            OBJECT{
                                    {KEY("subject"), STRING("hy150")},
                                    {KEY("grade"), NUMBER(7.5)}
                            }
                            }
                    },
                    {
                            KEY("courses"), ARRAY(
                            STRING("CS101"),
                                    STRING("CS201")
                    )
                    }
            }
    };

    // Ektypwsi olwn twn JSON antikeimenwn
    std::cout << "Empty Object: " << emptyObj << std::endl;
    std::cout << "Empty Array: " << emptyArray << std::endl;
    std::cout << "Some Number: " << someNumber << std::endl;
    std::cout << "True Value: " << isTrue << std::endl;
    std::cout << "False Value: " << isFalse << std::endl;
    std::cout << "Null Value: " << nothing << std::endl;
    std::cout << "Book: " << book << std::endl;
    std::cout << "Week Temperatures: " << week_temperatures << std::endl;
    std::cout << "Students: " << students << std::endl;

    return 0;
}
