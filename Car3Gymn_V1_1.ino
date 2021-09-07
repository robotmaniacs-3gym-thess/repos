/*  
 *Κωδικας Arduino Αυτοκινητάκι Εκδοση 1   
 *3ο Γυμνάσιο Θεσσαλονικης
 *Αμανατιάδου Γεωργία ΠΕ83
 *  Μαθητές:
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
 *    
 *    
 *    
 *    
  

  
  L298N Motor Controller
  
  
*/


//Ακροδέκτες αισθητήρα υπερήχων
int trig=11;   //ακροδέκτης 
int echo=12;   //ακροδέκτης
int dt=10;     //Μεταβλητή χρονοκαθυστέρησης


  
//Ακροδέκτες (pins) ελεγχου Μοτέρ
// MR  (Motor Right)
int MR_enable = 9;    //Ανοιγμα-Κλείσιμο και ταχύτητα
int MR_mprosta = 7;   //Κανονίζει κατεύθυνση
int MR_piso = 8;      //Κανονίζει κατεύθυνση
 
// ML  (Motor Left)
int ML_enable = 3;    //Ανοιγμα-Κλείσιμο και ταχύτητα
int ML_mprosta = 5;   //Κανονίζει κατεύθυνση
int ML_piso = 4;      //Κανονίζει κατεύθυνση





 
void setup()
{
  //pin αισθητήρα υπερήχων
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  
  // Όλα τα pins ελέγχου μοτέρ να γίνουν έξοδοι
  pinMode(MR_enable, OUTPUT);
  pinMode(ML_enable, OUTPUT);
  pinMode(MR_mprosta, OUTPUT);
  pinMode(MR_piso, OUTPUT);
  pinMode(ML_mprosta, OUTPUT);
  pinMode(ML_piso, OUTPUT);
 
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

void kinisi_empros(int taxitita)
{
  digitalWrite(MR_mprosta, HIGH);      // Δεξί μοτέρ κινηση εμπρός
  digitalWrite(MR_piso, LOW);
  analogWrite(MR_enable, taxitita);         // Δεξί μοτέρ ταχύτητα οσο είναι το όρισμα taxitita
  digitalWrite(ML_mprosta, HIGH);      // Αριστερό μοτέρ κινηση εμπρός
  digitalWrite(ML_piso, LOW);
  analogWrite(ML_enable, taxitita);         // Αριστερό μοτέρ ταχύτητα οσο είναι το όρισμα  taxitita
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
 
void loop()
 
{

  kinisi_empros (100);
  while (metrisi_apostasis() > 20)
    {
    delay(100);
    }
  motor_stop();
  delay(1000);
   
//  demoOne();  //κινηση μπρος πίσω
// 
//  delay(1000);
// 
//  demoTwo();  // επιτάχυνση - επιβράδυνση
// 
//  delay(1000);
 
}
