import sys
import random
from pyfiglet import Figlet

figlet = Figlet()
fonts = figlet.getFonts()

def main():
    if len(sys.argv) == 1:
        do_figlet()
    elif len(sys.argv) == 3 and sys.argv[1] in ["-f", "--font"]:
        font = sys.argv[2]
        if font in fonts: do_figlet(font)
        else: print("Invalid usage.")
    else:
        print("Invalid usage.")
        sys.exit(1)


def do_figlet(font=None):
    if font is None: figlet.setFont(font=random.choice(fonts))
    else: figlet.setFont(font=font)
    text = input("Input: ")
    print("Output:")
    print(figlet.renderText(text))


if __name__ == "__main__":
    main()