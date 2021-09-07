/*  
 * robotmaniacs-3gym-thess
 * https://github.com/robotmaniacs-3gym-thess/repos
 * 
 * Κωδικας Arduino Αυτοκινητάκι Εκδοση 1   
 * 3ο Γυμνάσιο Θεσσαλονικης
 * Αμανατιάδου Γεωργία ΠΕ83
 *     Μαθητές:
 *  Γ1,Γ2 3ου Γυμνασίου Θεσσαλονίκης, σχολικό έτος 2019-2020
 *  Γ1,Γ2 3ου Γυμνασίου Θεσσαλονίκης, σχολικό έτος 2020-2021
 *  
 *  
 *  
 *  
 *  
 *  
 *  
 *  Εκδοση 1
 *    Φορμαρισμα Κώδικα, δοκιμες μοτέρ ok, Σχόλια
 *  Έκδοση 1.1
 *    Δοκιμές 
 *    Τοποθέτηση δοκιμές Ultrasonic
 *    Πρόβλημα οταν υπήρχε servo στο pin 9-10-11, συνδεση servo στο pin 6, μετακινήσεις pin μοτερ σε νέες θέσεις
 *  Εκδοση 1.2
 *    Κωδικας, προχωρα μεχρι εμπόδιο στα 20cm, περιμενε 1s, συνέχισε μπροστά
 *  Έκδοση 1.3  
 *    Τοποθέτηση servo, 2ος οροφος σασι, ultrasonic σε ραστεράκι
 *    Δοκιμες κωδικα: προχωρα μεχρι εμπόδιο στα 20cm, στρίψε αριστερά, συνέχισε μπροστά
 *  Έκδοση 1.4
 *    Δοκιμή στροφής αισθητήρα ULTRASONIC αριστερά δεξιά σε εμπόδιο και στροφή στην καλύτερη πλευρά OK
 *  Έκδοση 1.5
 *    Δοκιμη σάρωσης + - 20 μοίρες στην κινηση ευθεία    // έγινε συμμάζεμα κωδικα της lοop και σχολιασμός
 *  Έκδοση 1.6
 *    Δοκιμή αισθητήρων γραμμής - συνδέσεις
  

  
  L298N Motor Controller
  
  
*/
#include<Servo.h>
Servo servo;   // στο pin 9

//Ακροδέκτες αισθητήρα υπερήχων
int trig=11;   //ακροδέκτης 
int echo=12;   //ακροδέκτης
int dt=10;     //Μεταβλητή χρονοκαθυστέρησης

int apostasi_mprosta;
int apostasi_aristera;
int apostasi_deksia;
int thesi_servo=0;
  
//Ακροδέκτες (pins) ελεγχου Μοτέρ
// MR  (Motor Right)
int MR_enable = 6;    //Ανοιγμα-Κλείσιμο και ταχύτητα
int MR_mprosta = 7;   //Κανονίζει κατεύθυνση
int MR_piso = 8;      //Κανονίζει κατεύθυνση
 
// ML  (Motor Left)
int ML_enable = 3;    //Ανοιγμα-Κλείσιμο και ταχύτητα
int ML_mprosta = 5;   //Κανονίζει κατεύθυνση
int ML_piso = 4;      //Κανονίζει κατεύθυνση


//Ακροδέκτες (pins) αισθητήρων IR (υπερύθρων)
int IR_Deksia = 0;
int IR_Kentro = 1;
int IR_Aristera = 2;
//Μεταβλητές μέτρησης αισθητήρων IR
int IR_D, IR_K, IR_A;

int tax_d = 150, tax_a=150;  //Ταχύτητες κίνησης οταν κινηται με αισθητήρες υπερύθρων

 
void setup()
{
  //pin αισθητήρα υπερήχων
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);

  //pin αισθητήρα υπερύθρων (IR) (ανιχνευσης γραμμής)
  pinMode(IR_Deksia, INPUT);
  pinMode(IR_Kentro, INPUT);
  pinMode(IR_Aristera, INPUT);

  // Όλα τα pins ελέγχου μοτέρ να γίνουν έξοδοι
  pinMode(MR_enable, OUTPUT);
  pinMode(ML_enable, OUTPUT);
  pinMode(MR_mprosta, OUTPUT);
  pinMode(MR_piso, OUTPUT);
  pinMode(ML_mprosta, OUTPUT);
  pinMode(ML_piso, OUTPUT);
  
  servo.attach(9);
  servo.write(90);
}


int metrisi_apostasis()
{
  int xronos, apostasi;
  
  digitalWrite(trig,HIGH);
  delay(dt);
  digitalWrite(trig,LOW);
  xronos = pulseIn(echo,HIGH);
  apostasi = (xronos/2) / 29.1;
  return apostasi;
}

void strofi_aristera(int taxitita, int xronos)
{
  digitalWrite(MR_mprosta, HIGH);      // Δεξί μοτέρ κινηση εμπρός
  digitalWrite(MR_piso, LOW);
  analogWrite(MR_enable, taxitita);         // Δεξί μοτέρ ταχύτητα οσο είναι το όρισμα taxitita
  digitalWrite(ML_mprosta, LOW);      // Αριστερό μοτέρ κινηση εμπρός
  digitalWrite(ML_piso, HIGH);
  analogWrite(ML_enable, taxitita);         // Αριστερό μοτέρ ταχύτητα οσο είναι το όρισμα  taxitita
  delay(xronos);
}

void strofi_deksia(int taxitita, int xronos)
{
  digitalWrite(MR_mprosta, LOW);      // Δεξί μοτέρ κινηση εμπρός
  digitalWrite(MR_piso, HIGH);
  analogWrite(MR_enable, taxitita);         // Δεξί μοτέρ ταχύτητα οσο είναι το όρισμα taxitita
  digitalWrite(ML_mprosta, HIGH);      // Αριστερό μοτέρ κινηση εμπρός
  digitalWrite(ML_piso, LOW);
  analogWrite(ML_enable, taxitita);         // Αριστερό μοτέρ ταχύτητα οσο είναι το όρισμα  taxitita
  delay(xronos);
}
void kinisi_empros(int taxitita)           // Ρουτίνα κίνησης με ιδιες ταχύτητες στα αριστερα και δεξιά μοτέρ
{
  digitalWrite(MR_mprosta, HIGH);      // Δεξί μοτέρ κινηση εμπρός
  digitalWrite(MR_piso, LOW);
  analogWrite(MR_enable, taxitita);         // Δεξί μοτέρ ταχύτητα οσο είναι το όρισμα taxitita
  digitalWrite(ML_mprosta, HIGH);      // Αριστερό μοτέρ κινηση εμπρός
  digitalWrite(ML_piso, LOW);
  analogWrite(ML_enable, taxitita);         // Αριστερό μοτέρ ταχύτητα οσο είναι το όρισμα  taxitita
}

void kinisi_empros2(int taxitita_deksia, int taxitita_aristera)   // Συμπληρωματική ρουτίνα με χωριστές ταχύτητες στα αριστερα και δεξιά μοτέρ
{
  digitalWrite(MR_mprosta, HIGH);      // Δεξί μοτέρ κινηση εμπρός
  digitalWrite(MR_piso, LOW);
  analogWrite(MR_enable, taxitita_deksia);         // Δεξί μοτέρ ταχύτητα οσο είναι το όρισμα taxitita
  digitalWrite(ML_mprosta, HIGH);      // Αριστερό μοτέρ κινηση εμπρός
  digitalWrite(ML_piso, LOW);
  analogWrite(ML_enable, taxitita_aristera);         // Αριστερό μοτέρ ταχύτητα οσο είναι το όρισμα  taxitita
}

void kinisi_piso(int taxitita)
{
  digitalWrite(MR_mprosta, LOW);      // Δεξί μοτέρ κινηση πίσω
  digitalWrite(MR_piso,HIGH );
  analogWrite(MR_enable, taxitita);         // Δεξί μοτέρ ταχύτητα οσο είναι το όρισμα taxitita
  digitalWrite(ML_mprosta, LOW);      // Αριστερό μοτέρ κινηση πίσω
  digitalWrite(ML_piso, HIGH);
  analogWrite(ML_enable, taxitita);         // Αριστερό μοτέρ ταχύτητα  οσο είναι το όρισμα taxitita 
}

void motor_stop()
{
  digitalWrite(MR_mprosta, LOW);
  digitalWrite(MR_piso, LOW);  
  digitalWrite(ML_mprosta, LOW);
  digitalWrite(ML_piso, LOW);  
}

void demoOne()
{
 
  // Συνάρτηση δοκιμής κίνησης μοτέρ εμπρός πίσω
 
  
  digitalWrite(MR_mprosta, HIGH);      // Δεξί μοτέρ κινηση εμπρός
  digitalWrite(MR_piso, LOW);
  analogWrite(MR_enable, 200);         // Δεξί μοτέρ ταχύτητα 200 (με μεγιστο 255)
 
  digitalWrite(ML_mprosta, HIGH);      // Αριστερό μοτέρ κινηση εμπρός
  digitalWrite(ML_piso, LOW);
  analogWrite(ML_enable, 200);         // Αριστερό μοτέρ ταχύτητα 200 (με μεγιστο 255)
 
  delay(2000);                         // Κίνηση για 2000mS   (2δ)
 
 
  // Αλλαγή κατεύθυνσης κινησης
  digitalWrite(MR_mprosta, LOW);       // Δεξί μοτέρ πίσω
  digitalWrite(MR_piso, HIGH);  
  digitalWrite(ML_mprosta, LOW);       //Αριστερό μοτέρ πίσω
  digitalWrite(ML_piso, HIGH); 
 
  delay(2000);                         // Κίνηση για 2000mS   (2δ)
  // Σβήσιμο κινητήρων
  digitalWrite(MR_mprosta, LOW);
  digitalWrite(MR_piso, LOW);  
  digitalWrite(ML_mprosta, LOW);
  digitalWrite(ML_piso, LOW);
 
}
 
void demoTwo()
 
{
  // Συνάρτηση δοκιμής κίνησης μοτέρ εμπρός πίσω με επιτάχυνση και επιβράδυνση
  // Ενεργοποίηση κινητήρων, ορισμός κατεύθυνσης
  digitalWrite(MR_mprosta, HIGH);
  digitalWrite(MR_piso, LOW);  
  digitalWrite(ML_mprosta, HIGH);
  digitalWrite(ML_piso, LOW); 
 
  // Επιτάχυνε από 0 στο μέγιστο
 for (int i = 0; i < 256; i++)
   {
    analogWrite(MR_enable, i);
    analogWrite(ML_enable, i);
    delay(20);
   } 
 
  // Επιβράδυνε από 255 ως 0
  for (int i = 255; i >= 0; --i)
  {
    analogWrite(MR_enable, i);
    analogWrite(ML_enable, i);
    delay(20);
  } 
  // Κλείσε μοτέρ
  digitalWrite(MR_mprosta, LOW);
  digitalWrite(MR_piso, LOW);  
  digitalWrite(ML_mprosta, LOW);
  digitalWrite(ML_piso, LOW);  
}

void apofasi_strofis_koita_aristera_deksia()
{
  servo.write(90);                          //Κοιτα μπροστά
  delay(1000);  
  apostasi_mprosta = metrisi_apostasis();   //Μετρα απόσταση μπροστά
  servo.write(180);                         //Κοίτα αριστερά
  delay(500);
  apostasi_aristera = metrisi_apostasis();  //Μέτρα απόσταση αριστερά
  servo.write(0);                           //Κοίτα δεξιά
  delay(1000);
  apostasi_deksia = metrisi_apostasis();    //Μέτρα απόσταση δεξιά
  servo.write(90);                          //Ξαναγύρνα μπροστά
                                            //---- ΑΠΟΦΑΣΗ ΣΤΡΟΦΗΣ 
  if( apostasi_aristera > apostasi_deksia)  //Αν εχεις πιο πολύ χώρο αριστερά
  {
    strofi_aristera( 120, 800);             //Στρίψε αριστερά
  } else                                    //Αλλιώς στρίψε δεξιά
  {
    strofi_deksia( 120, 800);
  }
  motor_stop();                             //Σταμάτα κίνηση
  delay(1000);
}

void apofasi_strofis_apli()
{
  servo.write(90);                          //Κοιτα μπροστά
  delay(1000);  
  strofi_aristera( 120, 800);             //Στρίψε αριστερά
  motor_stop();                             //Σταμάτα κίνηση
  delay(1000);
}
void sarosi_toy_servo_mprosta()
{
  switch(thesi_servo)                      // Στρίψε τον servo με τον Ultrasonic στην επόμενη θέση σάρωσης 
  {
    case 0: servo.write(90);break;         // θέση 0 στις 90 μοίρες   
    case 1: servo.write(100);break;        // θέση 1 στις 100 μοίρες
    case 2: servo.write(110);break;        // θέση 2 στις 110 μοίρες
    case 3: servo.write(100);break;        // θέση 3 στις 100 μοίρες
    case 4: servo.write(90);break;         // θέση 4 στις 90 μοίρες
    case 5: servo.write(80);break;         // θέση 5 στις 80 μοίρες
    case 6: servo.write(70);break;         // θέση 6 στις 70 μοίρες
    case 7: servo.write(80);break;         // θέση 7 στις 80 μοίρες
     
  }
  thesi_servo = thesi_servo+1;       // επόμενη θέση servo
  if (thesi_servo>7)                 // αν ειναι μεγαλύτερη της θέσης 7 γυρνα στην πρώτη (0)
  {
    thesi_servo = 0;  
  }
}
 
void loop()
{
  
  kinisi_empros2 (tax_d, tax_a);                       // Κινηση μπροστά με ταχύτητα 150

  IR_D = digitalRead(IR_Deksia);
  IR_K = digitalRead(IR_Kentro);
  IR_A = digitalRead(IR_Aristera);

  if ( (IR_D==1) && (IR_K==0) && (IR_A==1) )
    {
      tax_d=160;
      tax_a=160;
    }

  if ( (IR_D==0)  && (IR_A==1) )
    {
      tax_d=180;
      tax_a=50;
    }

  
  if ( (IR_D==1)  && (IR_A==0) )
    {
      tax_d=50;
      tax_a=180;
    }









}

///////// ΠΑΛΙΟΣ ΚΩΔΙΚΑΣ

/////  ΕΛΕΓΧΟΣ ΚΙΝΗΣΗΣ ΜΕ ΤΟΝ ΑΙΣΘΗΤΗΡΑ ULTRASONIC (απόστασης)
//  apostasi_mprosta = metrisi_apostasis();    // Μέτρα απόσταση μπροστά
//  while (apostasi_mprosta > 30)              // Οσο η απόσταση μπροστά είναι μεγάλη (πάνω από 30cm) 
//    {
//    sarosi_toy_servo_mprosta();            //Ειδικη ρουτίνα για σάρωση του Servo ωστε να βλέπει μπροστά από 70 ως 110 μοίρες
//    delay(150);                        //Καθυστέρηση από σάρωση σε σάρωση
//    apostasi_mprosta = metrisi_apostasis();   //Μέτρα απόσταση μπροστά
//    }
//  
//  motor_stop();
//  apofasi_strofis_koita_aristera_deksia();    //Στροφή με έλεγχο χώρου αριστερά δεξιά
//
//  //apofasi_strofis_apli();                  //Στριβει πάντα αριστερά
/////



//  kinisi_empros (100);
//  while (metrisi_apostasis() > 20)
//    {
//    delay(100);
//    }
//  motor_stop();
//  delay(1000);
   
//  demoOne();  //κινηση μπρος πίσω
// 
//  delay(1000);
// 
//  demoTwo();  // επιτάχυνση - επιβράδυνση
// 
//  delay(1000);
 
