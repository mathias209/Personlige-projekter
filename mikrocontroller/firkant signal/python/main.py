def freqCalc(n):
    freq=(2**(1/12))**(n-49)*440
    return round(freq)

start = 28
octave = 2
tones = ["C","CS","D","DS","E","F","FS","G","GS","A","AS","B"]

for key in range(100-(start-1)):
    if key % 12 == 0:
        octave+=1
        print()
    print(f"#define {tones[key % 12]}{octave} {freqCalc(key+start)}")

