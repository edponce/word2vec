
#word2vec_commented
This project is a functionally unaltered version of Google's published [word2vec implementation in C](https://code.google.com/archive/p/word2vec/), but which includes source comments. 

If you're new to word2vec, I recommending reading [my tutorial](http://mccormickml.com/2016/04/19/word2vec-tutorial-the-skip-gram-model/) first.

My focus is on the code in word2vec.c for training the skip-gram architecture with negative sampling, so for now I have ignored the CBOW and Hierarchical Softmax code. I also haven't looked much at the testing code.

Because the code supports both models and both training approaches, I highly recommended viewing the code in an editor which allows you to collapse code blocks. The training code is much more readable when you hide the implementations that you aren't interested in. 

## word2vec Model Training

word2vec training occurs in word2vec.c

Almost all of the functions in word2vec.c happen to be related to building and maintaining the vocabulary. If you remove the vocabulary functions, here's what's left:

* main() - Entry point to the script.
    * Parses the command line arguments.
* TrainModel() - Main entry point to the training process.
    * Learns the vocabulary, initializes the network, and kicks off the training threads.
* TrainModelThread() - Performs the actual training.
    * Each thread operates on a different portion of the input text file.

### Text Parsing
The word2vec C project does not include code for parsing and tokenizing your text. It simply accepts a training file with words separated by whitespace (spaces, tabs, or newlines). This means that you'll need to handle the removal of things like punctuation separately.

The code expects the text to be divided into sentences (with a default maximum length of 1,000 words). The end of a sentence is marked by two consecutive newlines "\n\n"; that is, there should be a blank line in between each sentence.

It also does not include the code for phrase recognition (e.g., treating "New York" as one word), though this was mentioned in their second paper "Distributed Representations of Words and Phrases and their Compositionality", and is clearly present in their published model trained on the Google News dataset. So phrase recognition would also need to be implemented separately, and then the phrases could be recorded in the training text using underscores in place of spaces. For example, United_States or New_York.

### Building the Vocabulary
`word2vec.c` includes code for constructing a vocabulary from the input text file.

The code supports fast lookup of vocab words through a hash table, which maps word strings to their respective `vocab_word` object. 

The completed vocabulary consists of the following:

* `vocab_word` - A structure containing a word and its metadata, such as its frequency (word count) in the training text.
* `vocab` - The array of `vocab_word` objects for every word.
* `vocab_hash` - A hash table which maps word hash codes to the index of the word in the `vocab` array. The word hash is calculated using the `GetWordHash` function.

Learning the vocabulary starts with the `LearnVocabFromTrainFile` function. Tokens from the training text are added to the vocabulary, and the frequency (word count) for each word is tracked.

If the vocabulary grows beyond 70% of the hash table size, the code will prune the vocabulary by eliminating the least frequent words. This is to minimize the occurrence (and performance impact) of hash collisions.
