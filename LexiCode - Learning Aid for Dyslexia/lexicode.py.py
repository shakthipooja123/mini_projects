import pyttsx3

engine = pyttsx3.init()
engine.setProperty('rate', engine.getProperty('rate') - 50)

confusable = {'p': 'p*', 'q': 'q**', 'b': 'b*', 'd': 'd**'}

def syllable(word):
    return "-".join(word)

def differentiate(word):
    return "".join(confusable.get(c, c) for c in word)

def speak(text):
    engine.say(text)
    engine.runAndWait()

def speak_letter_by_letter(text):
    for ch in text:
        if ch == " ":
            engine.say(" ")
        else:
            engine.say(ch)
    engine.runAndWait()

print("Lexicode Python – Learning Aid")
print("Enter your text (press Enter after each line; finish input with an empty line):")

lines = []
while True:
    line = input()
    if line.strip() == "":
        break
    lines.append(line)

processed_lines = []
for line in lines:
    processed_words = []
    for word in line.split():
        processed_words.append(syllable(differentiate(word)))
    processed_lines.append("   ".join(processed_words))

final_text = "\n".join(processed_lines)
print("\nProcessed Output:\n", final_text)

choice = ""
while choice not in ['y', 'n']:
    choice = input("\nEnable TTS? (y/n): ").strip().lower()

if choice == 'y':
    mode = ""
    while mode not in ['1', '2']:
        mode = input("Mode: 1-Normal  2-Letter-by-letter : ").strip()
    if mode == '2':
        speak_letter_by_letter(final_text)
    else:
        speak(final_text)
else:
    print("TTS disabled")
