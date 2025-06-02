# German/Italian Vocabulary Learner 

## Description

With this application you can locally run a vocabulary learner on your own PC, without any internet connection necessary. 
The Learner is made for german and italian. At compiliation a SQLite database will be initialized on your machine. And from there on everytime you
run the application it will communicate with your database.  
You can save german-italian word pairs and then let yourself be quizzed on them.


## Compile Instructions 

Before being able to run the application you have to follow these steps: 
+ install sqlite on your PC with the following command if you work on a linux machine:
  ```shell
  sudo apt install sqlite3
  ```
+ compile the files in your cloned repository with the following commands:
  ```shell
  mkdir build
  cd build
  cmake ..
  make -j8
  ./vokabeltrainer
  ```

  
## User Manual 

### Home Window

You'll see the home window where you can choose between going to:
+ the word saving window
+ the quiz window
+ the vocabulary list window
  
![grafik](https://github.com/user-attachments/assets/54d477e6-cba5-45bb-942b-9b12e5fab558)

### Word Saving Window

Here you can save your italian - german word pairs. First you are asked to put in the italian word and then the german word. You can either press 
the save button or press enter to save your word.  

![grafik](https://github.com/user-attachments/assets/03beaf1e-ecd7-4251-9af0-e91f33b21dea)

If your word has been saved it will tell you in a message under the input fields. If your word already exists 
in your database you'll also get a message that it is already saved and won't make a duplicate, so that your database stays clean and manageable.

![grafik](https://github.com/user-attachments/assets/669be6e3-7595-455c-a297-8265c429dc43)

You can add as many words to your database as you like, after every saving just press the reset button "Neues Wort" to get a fresh / clean input field. 
Additionally you can always go back to your homescreen with the home button.

### Quiz Window 

The quiz works in the way that when you have words saved in your database it will either generate a german or an italian word that you have to translate.

![grafik](https://github.com/user-attachments/assets/037e35a9-a5f8-407f-81d5-1ec117e946a2)

If your translation is correct it will tell you so, otherwise you'll get a message with the correct translation.

![grafik](https://github.com/user-attachments/assets/efd76bff-9260-4497-951d-309e67c3d10b)

You can always generate a new word to tranlate. Same as in the saving window you can always go back to the homescreen by clicking on the home button.

### Vocabulary List Window

If you navigate to your vocabulary list window you'll get a list of all the saved word-pairs in your database.

![grafik](https://github.com/user-attachments/assets/268bd720-4be6-4f6e-8e85-2503a48e1ec3)

When you click on a word you will get asked if you want to delete that word. If you click yes, that word will be deleted from your database and won't 
appear in your vocabulary list anymore.

![grafik](https://github.com/user-attachments/assets/cbeba062-0cbc-4049-88ae-453fd4bd2220)






