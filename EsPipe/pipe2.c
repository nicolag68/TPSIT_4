//Esercizio 2: Comunicazione bidirezionale tramite due Pipe
//Scrivere un programma C in cui il processo padre comunica con un processo figlio utilizzando due pipe anonime (pipe1 e pipe2).
//Il padre legge una stringa di testo inserita dall'utente da tastiera e la invia al figlio tramite pipe1. Il figlio legge la stringa da pipe1,
//la trasforma in lettere maiuscole, conta il numero di vocali presenti e salva entrambi i dati in una struttura C (struct Messaggio).
//Il figlio invia la struttura al padre tramite pipe2. Il padre legge la struttura da pipe2, attende la terminazione del figlio con wait(NULL)
//e stampa a schermo la stringa maiuscola e il numero di vocali.
int main() {

    return 0;

}
//non so farlo