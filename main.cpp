int main() {
    JSON(book) = OBJECT(
        {"title", STRING("Gone Girl")},
        {"author", OBJECT(
            {"firstname", STRING("Gillian")},
            {"sirname", STRING("Flynn")},
            {"age", NUMBER(45)})}
    );

    PRINT(book["title"]); // prints: Gone Girl
    PRINT(book["author"]); // prints: {firstname:"Gillian",sirname:"Flynn",age:45}
    PRINT(book); // prints the whole JSON for book
    PRINT(HAS_KEY(book, "author")); // prints: true
    PRINT(STRING("Book has key author? "), HAS_KEY(book, "author")); // prints: Book has key author? true

    return 0;
}
