Copy right 2015 Yogitha Renu Mahadasu

# AES_SquareAttack_4rounds
Python, C

Commands Executed:
Python SquareAttack.py > output_squareattack.txt
(To generate all the possible candidate keys – for the given 256 cipher texts, I got 1536 candidate keys)
To just get the integer values of the candidate keys generated in the Square Attack program:
Python SquareAttack.py > output_fed_4rnds.txt

Place the above generated output_fed_4rnds.txt in the AES folder and run AES in the following wake:

AES$ 	make
AES$ 	gcc rijndael-alg-fst.o 4rndsAttack.c –o attack
AES$ 	./attack > finalAnswer.txt
