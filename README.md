# Spam-Detection: Overview
This project is a very rudimentary program that uses binary dictionaries and uses the Bayes theorem to determine the probability of an email being either spam or "ham" (not spam).

The Naïve Bayes Spam Filter equation takes the probability of a spam occurring (P(A)), the probability of spam not occurring (P(B)), the conditional probability of a spam email occurring, given that a specific email is not spam also occurs (P(A/B)), and the conditional probability of event spam not occurring, given that a specific email is spam also occurs (P(B/A)). This forms into the equation: P(A|B) = P(B|A) * P(A) / P(B)

The conditional probability (P(A/B)) is what then determines if the email is considered to be spam or not spam.

#Spam-Detection: Project Structure
The SpamDetectionProject.cpp file contains all of the source code for this project. The twenty ".txt" files are to be used in tandem with the source code. The program prompts the user to input the name of the files exactly in the order of: training data, training class, test data and test class. With those file names, the project will then open the files, and run the Naïve Bayes equation to determine a spam or ham email.
