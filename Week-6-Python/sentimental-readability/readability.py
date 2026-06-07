def main():
    text = input("Text: ")
    grade_level = coleman_liau(text)
    
    if grade_level < 1: print("Before Grade 1")
    elif 1 <= grade_level <= 16: print(f"Grade {grade_level}")
    else: print("Grade 16+")

def coleman_liau(text):
    
    letter_counter = 0
    word_counter = 1
    sentence_counter = 0
    
    for c in text:
        if c.isalpha(): letter_counter += 1
        elif c == " ": word_counter += 1
        elif c in [".", "!", "?"]: sentence_counter += 1
        else: continue
    
    letters_avg = (letter_counter / word_counter) * 100.00
    sentences_avg = (sentence_counter / word_counter) * 100.00
    index = ((0.0588 * letters_avg) - (0.296 * sentences_avg)) - 15.8

    return round(index)

main()