from cs50 import get_string


def main():
    text = get_string("Text: ")
    index = calculateColemanLiauIndex(text)
    print(gradeLevel(index))


def calculateColemanLiauIndex(text):
    letters = numLetters(text)
    words = numWords(text)
    sentences = numSentences(text)

    L = letters * (100 / words)
    S = sentences * (100 / words)
    index = (0.0588 * L) - (0.296 * S) - 15.8
    return round(index)


def numLetters(text):
    numLetters = 0
    for i in range(len(text)):
        if text[i].isalpha():
            numLetters += 1

    return numLetters


def numWords(text):
    numSpaces = 0
    for i in range(len(text)):
        if text[i] == " ":
            numSpaces += 1
    numWords = numSpaces + 1

    return numWords


def numSentences(text):
    numSentences = 0
    for i in range(len(text)):
        if text[i] == '?' or text[i] == '!' or text[i] == '.':
            numSentences += 1

    return numSentences


def gradeLevel(index):
    if index < 1:
        return "Before Grade 1"
    elif index >= 16:
        return "Grade 16+"
    else:
        return f"Grade {index}"


main()
