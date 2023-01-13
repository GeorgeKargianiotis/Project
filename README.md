Ανάπτυξη Λογισμικού για Αλγοριθμικά Προβλήματα-Εργασία 1: Πολυγωνοποίηση Σημειοσυνόλου S το οποίο περιέχει n σημεία στον χώρο ℜ2

Τσίμπος Βασίλειος sdi1700172 Καργιανιώτης Γεώργιος sdi1900075

Υλοποίηση των αλγορίθμων incremental, convex_hull (αυξητικός και με βάση το ΚΠ)

ΔΟΜΗ ΤΟΥ ΚΩΔΙΚΑ ΚΑΙ ΑΡΧΕΙΑ:

Το project έχει δομηθεί σε δύο φακέλους, για καλύτερη οργάνωση του κώδικα Όλα τα αρχεία κεφαλίδας βρίσκονται στον φάκελο headers, που περιλαμβάνονται οι δηλώσεις των πηγαίων αρχείων, των namespaces και των βιβλιοθηκών της CGAL Τα πηγαία αρχεία βρίσκονται στον φάκελο sources To βασικό πρόγραμμα που εκτελείται για την δοκιμή των αλγορίθμων είναι το polygonization.cpp

ΤΡΟΠΟΣ ΕΚΤΕΛΕΣΗΣ:

1.Για την δημιουργία του make file εκτελούμε cmake -DCGAL_DIR=$HOME/lib/CGAL -DCMAKE_BUILD_TYPE=Release όπου $HOME το directory που είναι εγκατεστημένη η CGAL.

2.Εκτέλεση της make εντολής

3.Εκτέλεση του εκτελέσιμου ./polygonization. Τα ορίσματα μπορούν να δοθούν με όποια σειρά θέλει ο χρήστης
Το project έχει δομηθεί σε δύο φακέλους, για καλύτερη οργάνωση του κώδικα
Όλα τα αρχεία κεφαλίδας βρίσκονται στον φάκελο headers, που περιλαμβάνονται οι δηλώσεις των πηγαίων αρχείων, των namespaces και των βιβλιοθηκών της CGAL 
Τα πηγαία αρχεία βρίσκονται στον φάκελο sources
To βασικό πρόγραμμα που εκτελείται για την δοκιμή των αλγορίθμων είναι το polygonization.cpp

ΤΡΟΠΟΣ ΕΚΤΕΛΕΣΗΣ: 

1) Για την δημιουργία του make file εκτελούμε cmake -DCGAL_DIR=$HOME/lib/CGAL -DCMAKE_BUILD_TYPE=Release
   όπου $HOME το directory που είναι εγκατεστημένη η CGAL.
2) Εκτέλεση της make εντολής
3) Εκτέλεση του εκτελέσιμου ./polygonization. Τα ορίσματα μπορούν να δοθούν με όποια σειρά θέλει ο χρήστης


ΠΕΡΙΓΡΑΦΗ ΥΛΟΠΟΙΗΣΗΣ ΤΩΝ ΑΛΓΟΡΙΘΜΩΝ:

ΑΥΞΗΤΙΚΟΣ:

Υλοποίηση στο αρχείο incremental.cpp

1.Ταξινόμηση σημείων και σχηματισμός αρχικού τριγώνου (πολυγώνου) Αν τα τρία πρώτα σημεία είναι συνευθειακά, προστίθονται και άλλα σημεία μέχρι να σχηματιστεί ένα τρίγωνο.
2.Εύρεση ΚΠ (κυρτό πολύγωνο) με χρήση συναρτήσεων της CGAL
3.Θέτουμε την κατεύθυνση του ΚΠ και του ΑΠ (απλό πολύγωνο) αντίθετη από την φορά του ρολογιού. Βοηθάει στην εισαγωγή του σημείου στο ΑΠ
4.Εύρεση Κόκκινων ακμών του ΚΠ. Αν μια κόκκινη ακμή ανήκει και στο ΑΠ εισάγεται κατευθείαν στις ορατές για βελτίωση απόδοσης, εκτός αν το νέο σημείο είναι συνευθειακό με την ακμή
5.Εύρεση ορατών ακμών για κάθε edge του πολυγώνου. Ο έλεγχος γίνεται αμέσως μόλις βρεθεί μια κόκκινη ακμή
6.Επιλογή ορατής ακμής με βάση τα κριτήρια της εκφώνησης (επιλογή από τον χρήστη)
7.Εισαγωγή του νέου σημείου στο ΑΠ
8.Υπολογισμός του εμβαδού του τριγώνου που σχηματίζει το νέο σημείο με την ακμή που καταργεί και προσθήκη αυτού στο συνολικό εμβαδό.
9.Επανάληψη της διαδικασίας μέχρι να ισαχθούν όλα τα σημεία στο ΑΠ
10.Εκύπωση πολυγώνου, χρόνου, και όλων των απαραίτητων πληροφοριών
1)   Ταξινόμηση σημείων και σχηματισμός αρχικού τριγώνου (πολυγώνου)
     Αν τα τρία πρώτα σημεία είναι συνευθειακά, προστίθονται και άλλα σημεία μέχρι
     να σχηματιστεί ένα τρίγωνο.
3)   Εύρεση ΚΠ (κυρτό πολύγωνο) με χρήση συναρτήσεων της CGAL
4)   Θέτουμε την κατεύθυνση του ΚΠ και του ΑΠ (απλό πολύγωνο) αντίθετη από 
     την φορά του ρολογιού. Βοηθάει στην εισαγωγή του σημείου στο ΑΠ
5)   Εύρεση Κόκκινων ακμών του ΚΠ. Αν μια κόκκινη ακμή ανήκει και στο
     ΑΠ εισάγεται κατευθείαν στις ορατές για βελτίωση απόδοσης, εκτός
     αν το νέο σημείο είναι συνευθειακό με την ακμή
6)   Εύρεση ορατών ακμών για κάθε edge του πολυγώνου. Ο έλεγχος
     γίνεται αμέσως μόλις βρεθεί μια κόκκινη ακμή
7)   Επιλογή ορατής ακμής με βάση τα κριτήρια της εκφώνησης (επιλογή από τον χρήστη)
8)   Εισαγωγή του νέου σημείου στο ΑΠ
9)   Υπολογισμός του εμβαδού του τριγώνου που σχηματίζει το νέο σημείο
     με την ακμή που καταργεί και προσθήκη αυτού στο συνολικό εμβαδό.
10)  Επανάληψη της διαδικασίας μέχρι να ισαχθούν όλα τα σημεία στο ΑΠ
11)  Εκύπωση πολυγώνου, χρόνου, και όλων των απαραίτητων πληροφοριών

ΜΕ ΒΑΣΗ ΤΟ ΚΠ:

Υλοποίηση στο αρχείο convex_hull.cpp

1.Εισαγωγή όλων των σημείων και σχηματισμός αρχικού πολυγώνου
2.Αρχικοποίηση ΚΠ
3.Για κάθε ακμή του νέου πολυγώνου, εύρεση πλησιέστερου σημείου
4.Με βάση κριτηρίων, επιλογή κατάλληλου ζευγαριού ακμής-νέου σημείου
5.Έλεγχος ορατότητας νέου σημείου
6.Αφαίρεση παλιάς ακμής και εισαγωγή του σημείου μαζί με τις 2 νέες ακμές
7.Εάν υπάρξει εξωτερικό σημείο από αυτήν την προσθήκη, αναίρεση αλλαγών και επιλογή άλλου ζεύγους
8.Επανάληψη μέχρι να προστεθούν όλα τα εσωτερικά σημεία
9.Έλεγχος πολυγώνου και εκτύπωση ζητουμένων


Και στα δύο αρχεία υπάρχει επεξήγηση κάθε διαδικασίας του αλγορίθμου με σχόλια

utils.cpp To αρχείο αυτό υπάρχει για την διευκόλυνση των συμμετεχόντων. Εκεί υπάρχει η υλοποίηση μερικών συναρτήσεων που χρειάζονται οι αλγόριθμοι cgalConfig.hpp Περιλαμβάνονται δηλώσεις templates της βιβλιοθήκης cgal.

Η ανάπτυξη του λογισμικού έγινε σε συνεργασία, με την χρήση του github. Περιλαμβάνεται ο φάκελος .git repo --> https://github.com/GeorgeKargianiotis/Project

Ανάπτυξη Λογισμικού για Αλγοριθμικά Προβλήματα-Εργασία 2: Πολυγωνοποίηση σημειοσυνόλου βέλτιστης επιφάνειας

Τσίμπος Βασίλειος sdi1700172 Καργιανιώτης Γεώργιος sdi1900075

Υλοποίηση των αλγορίθμων local_search, simulated_annealing

ΔΟΜΗ ΤΟΥ ΚΩΔΙΚΑ ΚΑΙ ΑΡΧΕΙΑ:

Το project έχει δομηθεί σε δύο φακέλους, για καλύτερη οργάνωση του κώδικα Όλα τα αρχεία κεφαλίδας βρίσκονται στον φάκελο headers, που περιλαμβάνονται οι δηλώσεις των πηγαίων αρχείων, των namespaces και των βιβλιοθηκών της CGAL Τα πηγαία αρχεία βρίσκονται στον φάκελο sources To βασικό πρόγραμμα που εκτελείται για την δοκιμή των αλγορίθμων είναι το optimal.polygon.cpp

ΤΡΟΠΟΣ ΕΚΤΕΛΕΣΗΣ:

1.Για την δημιουργία του make file εκτελούμε cmake -DCGAL_DIR=$HOME/lib/CGAL -DCMAKE_BUILD_TYPE=Release όπου $HOME το directory που είναι εγκατεστημένη η CGAL.

2.Εκτέλεση της make εντολής

3.Εκτέλεση του εκτελέσιμου ./optimal_polygon. Τα ορίσματα μπορούν να δοθούν με όποια σειρά θέλει ο χρήστης
ΠΕΡΙΓΡΑΦΗ ΥΛΟΠΟΙΗΣΗΣ ΤΩΝ ΑΛΓΟΡΙΘΜΩΝ:

LOCAL SEARCH

Υλοποίηση στο αρχείο local_search.cpp

1.Αρχικοποίηση πολυγώνου από Εργασία 1
2.Όσο η αλλγαή δεν είναι αμελητέα (με βάση το threshold):
    2α.Για κάθε ακμή του πολυγώνου
    2β.Για όλα τα σημεία, έλεγχος κάθε σημείου και σχημτισμός αλυσίδας όσο πληρούνται οι περιορισμοί
    2γ.Έλεγχος ορατότητας και simplicity μετά από κάθε αλλαγή
    2δ.Αναίρεση αλλαγής σε περίπτωση σφάλματος
    2ε.Εάν υπήρξε αλλαγή που προσθέτει ή αφαιρεί από το εμβαδόν (ανάλογα την περίπτωση), αποθήκευση σημείου ή αλυσίδας για αλλαγή
3.Εφαρμογή όλων των αλλαγών
4.Υπολογισμό νέου εμβαδού και ενημέρωση threshold
5.Επανάληψη διαδικασίας

ΠΑΡΑΔΟΧΕΣ ΑΛΓΟΡΙΘΜΟΥ LOCAL SEARCH
1. Ο αλγόριθμος εξετάζει ξεχωριστά κάθε σημείο του πολυγώνου και δημιουργεί την αλυσίδα. Αν βρεθεί όμως προβληματικό σημείο και έχυοεμ ακόμα χώρο, δηλαδή για L=10 έχουμε ήδη 5 και βρούμε κάποιο που δεν πληρεί τις προυποθέσεις, τα επόμενα κατάλληλα σημεία θα χρησιμοποιηθούν για την ολοκλήρωση της ακολουθίας. Επομένως, η αλυσίδα δεν χρειάζεται απαραίτητα να είναι συνεχόμενη

2. Για την αποθήκευση των αλλαγών χρησιμοποιείται η δομή change, ορισμένη το αρχείο .hpp. Αποθηκεύεται η κάθε αλυσίδα σημείων μαζί με το edge μετά από το οποίο θα γίνει η εισαγωγή (edge.end() δηλαδή). Μετά την εξέταση όλων των σημείων για ένα edge, όλες οι αλλαγές αποθηκεύονται σε ένα Vector και εφαρμόζονται πριν εξετάσουμε το επόμενο edge

1) Εισαγωγή όλων των σημείων και σχηματισμός αρχικού πολυγώνου
2) Αρχικοποίηση ΚΠ
3) Για κάθε ακμή του νέου πολυγώνου, εύρεση πλησιέστερου σημείου
4) Με βάση κριτηρίων, επιλογή κατάλληλου ζευγαριού ακμής-νέου σημείου
5) Έλεγχος ορατότητας νέου σημείου
6) Αφαίρεση παλιάς ακμής και εισαγωγή του σημείου μαζί με τις 2 νέες ακμές
7) Εάν υπάρξει εξωτερικό σημείο από αυτήν την προσθήκη, αναίρεση αλλαγών και επιλογή άλλου ζεύγους
8) Επανάληψη μέχρι να προστεθούν όλα τα εσωτερικά σημεία
9) Έλεγχος πολυγώνου και εκτύπωση ζητουμένων

Και στα δύο αρχεία υπάρχει επεξήγηση κάθε διαδικασίας του αλγορίθμου με σχόλια

utils.cpp	 To αρχείο αυτό υπάρχει για την διευκόλυνση των συμμετεχόντων. Εκεί υπάρχει η υλοποίηση μερικών συναρτήσεων που χρειάζονται οι αλγόριθμοι
cgalConfig.hpp   Περιλαμβάνονται δηλώσεις templates της βιβλιοθήκης cgal.

Η ανάπτυξη του λογισμικού έγινε με την χρήση του github. Περιλαμβάνεται ο φάκελος .git
repo --> https://github.com/GeorgeKargianiotis/Project




Ανάπτυξη Λογισμικού για Αλγοριθμικά Προβλήματα: Εργασία 3 - Τελειοποίηση πολυγωνοποίησης σημειοσυνόλου βέλτιστης επιφάνειας, ανάπτυξη εφαρμογής για τη συγκριτική αξιολόγηση των αλγόριθμων πολυγωνοποίησης και διαγωνισμός.

Καργιανιώτης Γεώργιος sdi1900075

Η ανάπτυξη του λογισμικού έγινε με την χρήση του github. Περιλαμβάνεται ο φάκελος .git
repo --> https://github.com/GeorgeKargianiotis/Project

Η δομή των αρχείω και η εκτέλεση του κώδικα είναι ακριβώς η ίδια με αυτήν της 2η εργασίας με την προσθήκη ενός ακόμα arguemnt, 1 για incremental και 0 για convex hull. 

./evaluate <ορίσματα 2ης εργασίας + 1 ή 0>

ΔΟΜΗ ΤΟΥ ΚΩΔΙΚΑ ΚΑΙ ΑΡΧΕΙΑ:

Το project έχει δομηθεί σε δύο φακέλους, για καλύτερη οργάνωση του κώδικα Όλα τα αρχεία κεφαλίδας βρίσκονται στον φάκελο headers, που περιλαμβάνονται οι δηλώσεις των πηγαίων αρχείων, των namespaces και των βιβλιοθηκών της CGAL Τα πηγαία αρχεία βρίσκονται στον φάκελο sources To βασικό πρόγραμμα που εκτελείται για την δοκιμή των αλγορίθμων είναι το evaluate.cpp

ΤΡΟΠΟΣ ΕΚΤΕΛΕΣΗΣ:

1.Για την δημιουργία του make file εκτελούμε cmake -DCGAL_DIR=$HOME/lib/CGAL -DCMAKE_BUILD_TYPE=Release όπου $HOME το directory που είναι εγκατεστημένη η CGAL.

2.Εκτέλεση της make εντολής

3.Εκτέλεση του εκτελέσιμου ./evaluate. Τα ορίσματα μπορούν να δοθούν με όποια σειρά θέλει ο χρήστης, εκτός από το τελευταίο



ΤΕΛΙΚΕΣ ΠΑΡΑΤΗΡΗΣΕΙς ΓΙΑ ΤΟ OUTPUT:

Οι αλγόριθμοι convex hull και incremental τερματίζουν άμεσα για 10 και 100 σημεία, ενω ο χρόνος για 1000+ αυξάνεται εκθετικά, ειδικά στον convex hull που εξαρτάται άμεσα από ήδη υπάρχον πολύγωνο και όλα τα σημεία του

Έγιναν δοκιμές σε σύνολα μεγέθους μέχρι 3000 σημεία, στο simulation annealing με local και global step.
Γενική παρατήρηση είναι πως, το μέγεθος του σημειοσυνόλου, επηρεάζει πάρα πολύ τον χρόνο εκτέλεσης. Ενδεικτικά
αναφέρεται ότι για τα 100 σημεία με global step και L = 10, το πρόγραμμα τερματίζει σε 0,2 δευτερόλπετα, για 1000 σημεία, το
πρόγραμμα τερματίζει σε 70 δευτερόλεπτα και για 3000 σημεία 10 λεπτά.

Ο local search χρειάζεται περισσότερο χρόνο από τον simulated annealing ή simulated with subdivision  αφού διατρέχει πολλές φορές το ίδιο πολύγωνο

Αποτελέσματα για 10000+ σημεία δεν είναι εφιτκοί, αφου χρειάζονται υπολογσισμοί και μετά το πέρας των 24 ωρών 

(Οι επιλογές των threshholds και L γίνονται από τον χρήστη)