static int data_size = 6;
String xLabel = "Time";
String yLabel = "Sensor value";
String Heading = "Results of Arduino";

int leftMargin=80;

int divisionWidth =  5;


void setup(){
  
  size(720,480);
  int[] count = new int[data_size];
  int[] yval = new int[data_size];
  color[] c = new color[data_size];
  
  for (int i=0;i<count.length;i++)
    count[i] = i;
  
  for (int i=0;i<yval.length;i++)
    yval[i] = (int)random(5, 100);
  
  
  for(int i=0; i<c.length;i++)
    c[i] = color(random(0,255),random(0,255),random(0,255));
  
  Axis();
  Headings();
  barGraph(count,yval,c);


}
void Headings(){
  fill(0);
  textSize(15);
  text(xLabel,leftMargin+50,120);
  
  textSize(15);
  rotate(PI/2.0);
  text(yLabel,10,-60);
  rotate(PI/-2.0);


}

void barGraph(int count[], int yval[], color c[]){
  rectMode(CORNERS);
  
  for(int i=0;i<count.length;i++){
  fill(c[i]);
  rect(leftMargin+count[i]*20+5,100-yval[i],leftMargin+count[i]*20+20,100);
  textSize(10);
  fill(0);
  text(yval[i],leftMargin+count[i]*20+15/2,100-yval[i]);
  }
 
}

void Axis(){
  stroke(0);
  line(leftMargin,100,leftMargin+30+data_size*20,100);
  stroke(0);
  line(leftMargin,1,leftMargin,100);
  
  stroke(120);
  for(int i=1; i<10;i++)
  line(leftMargin,100-i*10,leftMargin+30+data_size*20,100-i*10);
  noStroke();
}