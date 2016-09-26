static int data_size = 6;
String xLabel = "X axis";
String yLabel = "Y axis";
String Heading = "Results of Arduino";

int leftMargin=80;

class InPoint{
  int pointX = 0;
  int pointY = 0;
  
  public void setX(int inX){
    this.pointX = inX;
  }
  public void setY(int inY){
    this.pointY = inY;
  }
}

void setup(){
  
  size(720,480);
  color[] c = new color[data_size];
  InPoint[] pArr = new InPoint[data_size];
  
  
  //random data set
  for (int i=0;i<data_size;i++){
    pArr[i] = new InPoint();
    pArr[i].setX(leftMargin+i*20+20);
    pArr[i].setY(100-(int)random(5, 100)); 
 }
  
  for(int i=0; i<c.length;i++)
    c[i] = color(random(0,255),random(0,255),random(0,255));
  
  Axis();
  Headings();
  pointGraph(pArr);
  printBar(pArr);

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

void pointGraph(InPoint pArr[]){
  
  for(int i=0;i<data_size;i++){
  strokeWeight(4);
  point(pArr[i].pointX,100-pArr[i].pointY);
  textSize(9);
  text(pArr[i].pointY,leftMargin+i*20+20-2,100-pArr[i].pointY-2);
  }
 
}

void printBar(InPoint pArr[]){
  strokeWeight(1);
  for(int i=0;i<data_size-1;i++){
  line(pArr[i].pointX,100-pArr[i].pointY,pArr[i+1].pointX,100-pArr[i+1].pointY);
  }

}

void Axis(){
  stroke(0);
  line(leftMargin,100,leftMargin+30+data_size*20,100);
  stroke(0);
  line(leftMargin,1,leftMargin,100);
  
}