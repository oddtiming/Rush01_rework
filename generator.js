/**
 * Can be compiled on codepen.io
 * original code from
 * https://codepen.io/rs_zdjn/pen/dyoYJjo?editors=0010
 */

//Global Variables//
var  solution, col, squares, clueSquares=[], clearBoard, newPuzzle, solve, checkSolution, hintButton, hints,htext;


var  PZ_SIZE = 8;
var  values_str = "12345678";
var	 input_arr = [1,2,3,4,5,6,7,8];


//P5 Setup//
function setup(){
  createCanvas(screen.width, screen.height);
  background(0,200,200,50);
  
  col= color(0,100,100);
  title = createP("Skyscraper")
    .addClass("title")
    .position(130,-50);
  
  hints=false;
 
  setClues(); 
 
  clearBoard=createButton("CLEAR")
    .position(squares[PZ_SIZE - 1].x+170,squares[0].y)
    .mousePressed(setBoard);
  
  newPuzzle=createButton("NEW PUZZLE")
    .position(squares[PZ_SIZE - 1].x+170, squares[0].y+25)
    .mousePressed(setup);
  
  checkSolution=createButton("CHECK")
    .position(squares[PZ_SIZE - 1].x+170,squares[0].y+50)
    .mousePressed(check);
  
  solve=createButton("SOLVE")
    .position(squares[PZ_SIZE - 1].x+170, squares[0].y+75)
    .mousePressed(setSolution);
  
  
  hintButton=createButton("TOGGLE PENCIL MARKS")
    .style("font-size","12px")
    .position(squares[PZ_SIZE - 1].x+170, squares[0].y+100)
    .mousePressed(h);
  
  
}

//Game Board Functions//
function setBoard(){
  squares = [];
  for(var i = 0; i < PZ_SIZE; i++){
   for(var j = 0; j < PZ_SIZE; j++){
     var s = new Square(i,j);
     s.inp.input(responsiveFont);
     squares.push(s);
    }
  }
  //squares.forEach(sq=>sq.display());
  return squares;
}
function setClues(c=generatePuzzle()){
  squares = setBoard();
  gotSolution=false;
  clues = c;
  clueSquares=[];
  let clueSet=sortClues(clues.slice());
  
  for(var i = 0; i < PZ_SIZE; i++){
    clueSquares.push(new Clue(clueSet.r[i][0], "row",i,0));
    clueSquares.push(new Clue(clueSet.r[i][1], "row", i, 1));
    clueSquares.push(new Clue(clueSet.c[i][0], "col", i,0));
    clueSquares.push(new Clue(clueSet.c[i][1], "col", i, 1));
  }
  
  return clues;
}
function extractClues(){
  let top = clueSquares.filter(e=>e.pos=="top"?e:false)
        .map(e=>e.inp.value()>0?parseInt(e.inp.value()):0),
      bottom = clueSquares.filter(e=>e.pos=="bottom")
        .map(e=>e.inp.value()>0?parseInt(e.inp.value()):0),
      left = clueSquares.filter(e=>e.pos=="left")
        .map(e=>e.inp.value()>0?parseInt(e.inp.value()):0),
      right=clueSquares.filter(e=>e.pos=="right")
        .map(e=>e.inp.value()>0?parseInt(e.inp.value()):0);
 
  return top.concat(right)
    .concat(bottom.reverse())
    .concat(left.reverse());  
}
function getSolution(){
  clues = extractClues();
  try{
    var s= solvePuzzle(clues);
  }
  catch(e){
    alert("Invalid Puzzle. Check clues and try again."); 
    return false;
   }
  let sol = [];
  for(let row of s){
    sol=sol.concat(row);
  }
  solution = sol;
  gotSolution=true;
  return sol;
}
function setSolution(){
  clues = extractClues();
  solution = getSolution();
  if(solution){
  squares.forEach((sq, i)=>{
    sq.inp.style("font-size", "20px")
      .style("color", "black");
    sq.inp.value(solution[i]);
  });
  }
}
function check(){
  let s = getSolution();
  var solved = true;
  squares.forEach((sq,i)=>{
    if(!sq.inp.value() || sq.inp.value().length > 1){
      sq.inp.style("color",col);
    }
    else if(solution[i] != sq.inp.value()){
      sq.inp.style("color","red");
      solved = false;
    }
  });
  return solved;
}
function responsiveFont(){
  if(this.value().length > 1){
    this.style("font-size", 10+"px")
      .style("color",col );
  }else{
    this.style("font-size", 20+"px")
      .style("color", "black");
    this.hints=false;
  }
}
function setHints(){
    for(var sq of squares){
      if(!sq.inp.value() ){
        sq.hints=true;
        sq.inp.style("font-size", 10+"px")
          .style("color",col)
          .value(values_str + "\n"
                 .split("")
                 .filter(e=>!getHints(sq.row, sq.column)
                         .includes(e))
                 .join(""));
      }
    else if( sq.inp.value().length > 1){
      let z =sq.inp.value()
            .split("")
            .filter(e=>!getHints(sq.row, sq.column).includes(e));
      sq.inp.value(z.join(""));
    }
      
    }
           
}
function getHints(row,col){
 let sets= squares
 .filter(e=>e.inp.value().length==1 
          && (e.row==row||e.column==col))
 .map(e=>e.inp.value());
  
  return sets;
}
function keyReleased(){
  if(hints){
    setHints();
  }
}
function h(){
  hints= !hints;
  if(hints){
     
    setHints();
  }
  else{
    
    for(let i = 0; i < squares.length; i++){
      if(squares[i].inp.value().length > 1){
        squares[i].inp.value("");
      }
    }
  }
  return hints;
  
}
/////Classes/////
class Square{
  constructor(row, column,val=0){
    this.row=row;
    this.column=column;
    this.x=this.column*50+140;
    this.y=this.row*50+180;
    this.inp = createInput(val)
      .position(this.x+12,this.y+12);
    this.hint=false;
  }
  // display(s=0){
  //   push();
  //    fill(255);
  //    strokeWeight(1);
  //    rect(this.x,this.y,50,50); 
  //   pop();
  // }
}
class Clue{
  constructor(val,type,n,p){
    this.type=type;
    this.value=val;
    this.pos=type=="row"?p==0?"left":"right":p==0?"top":"bottom";
    this.x,this.y;
    if(type=="row"){
      if(p==0){
        this.x = squares[0].x-40;
      }else{
        this.x=squares[PZ_SIZE - 1].x+50+15;
      }
      this.y = squares[n*PZ_SIZE].y+12;
    }
    else{
      if(p==0){
        this.y = squares[0].y-40;
      }else{
        this.y=squares[48].y+65;
      }
      this.x= squares[n].x+12;
    }
    
    this.inp=createInput(val)
      .style("font-size", 20+"px")
      .style("border","1px dashed gray")
      .style("border-radius", "10%")
      .position(this.x,this.y);
  } 
}





/////////////////////////////////////////////////
//SOLVER FUNCTIONS// 
var usedChars = [],
    input_arr;
//create all permutations of input
function permute(input, permArr=[]) {
  var i, ch;
  for (i = 0; i < input.length; i++) {
    ch = input.splice(i, 1)[0];
    usedChars.push(ch);
    if (input.length == 0) {
      permArr.push(usedChars.slice());
    }
    permute(input, permArr);
    input.splice(i, 0, ch);
    usedChars.pop();
  }
  return permArr
} 
const perms = permute(input_arr),
      SIZE=PZ_SIZE;

class Tower{
  constructor(clues){
    this.clueSet=sortClues(clues.slice());
    this.r=this.clueSet.r.map(e=>getPoss(e));
    this.c=this.clueSet.c.map(e=>getPoss(e));
    this.grid=[[0,0,0,0,0,0,0],[0,0,0,0,0,0,0],[0,0,0,0,0,0,0],[0,0,0,0,0,0,0],[0,0,0,0,0,0,0],[0,0,0,0,0,0,0],[0,0,0,0,0,0,0]];
    
    this.cellPoss=[];
    this.c=crossCheck(this.c,this.r);
    this.r=crossCheck(this.r,this.c);
    this.runs = 0;
    this.apply();
  }
  cells(grid){
    var g=[];
    for(let i = 0; i < this.grid.length; i++){
     var r=[];
      for(let j = 0; j < this.grid[i].length; j++){
        r.push(this.getCellPoss(i,j));
      }
      g.push(r);
    }
    
    return g;
  }
  apply(){
     this.runs++;
     for(let i = 0; i < this.grid.length; i++){
      if(this.grid[i].includes(0)){
        for(let j = 0; j < this.grid[i].length; j++){
          if(this.grid[i][j]==0){
            if(checkElement(this.r[i][0][j], j, this.r[i])){
              this.grid[i][j]=this.r[i][0][j];
              this.r=filterPossible(this.r, i,j,this.grid[i][j]);
              this.c=filterPossible(this.c,j,i,this.grid[i][j]);
              this.c=crossCheck(this.c,this.r);
              this.r=crossCheck(this.r,this.c);
            }
            if(checkElement(this.c[j][0][i], i, this.c[j])){
              this.grid[i][j]=this.c[j][0][i];
              this.r=filterPossible(this.r, i,j,this.grid[i][j]);
              this.c=filterPossible(this.c,j,i,this.grid[i][j]);
              this.c=crossCheck(this.c,this.r);
              this.r=crossCheck(this.r,this.c);
            }
          }
        }
      }
    }
     
    if(!this.isSolved(this.grid) && this.runs < 100){
      return this.apply();
    }
     return this;
   }
  getCellPoss(row, col){
    let rp=Array.from(new Set(this.c[col].map(e=>e[row])));
    let cp=Array.from(new Set(this.r[row].map(e=>e[col])));
    let res= rp.filter(e=>cp.includes(e));
    
    return res.length===0?false:res.sort();
  }
  rowPoss(row){
    var res = [];
    for(let i = 0; i < this.grid[row].length; i++){
      res.push(this.getCellPoss(row, i));
    }
    
    return res;
  }
  isSolved(grid){
    if(grid.join("").includes("0")){
      return false;
    }
    let r = grid.slice().map((row, i)=>getClue(row));
    let c = rotateGrid(grid.slice()).map(col=>getClue(col));
    
    for(let i = 0; i < r.length; i++){
      r[i]=r[i].every((e,j)=>
                      this.clueSet.r[i][j]==0 
                      || this.clueSet.r[i][j]==r[i][j]);
      
      c[i]=c[i].every((e,j)=>
                      this.clueSet.c[i][j]==0 
                      || this.clueSet.c[i][j]==c[i][j]);
      
      if(!r || !c){
        return false;
      }
    }
    return true;
  }
}
function solvePuzzle(clues){
  var t = new Tower(clues);
  t.apply();
  
  if(t.grid.join("").includes(0)){
   t=guess(t, clues);
  }
  
 return t.grid;
}

function sortClues(clues){
  var c=[clues.splice(0,SIZE), 
         clues.splice(0,SIZE), 
         clues.splice(0,SIZE), 
         clues.splice(0,SIZE)];
  return {
    c:c[0].map(e=>[e,c[2].pop()]),
    r:c[1].map(e=>[c[3].pop(),e])
  };
}
function getClue(a){
  let vis=[0,0],
      sky=[0,0],
      l=a.length-1;
  
  for(let i = 0; i < a.length; i++){
    if(a[i]>sky[0]){
      sky[0]=a[i];vis[0]++;
    }
    if(a[l-i]>sky[1]){
      sky[1]=a[l-i]; vis[1]++;
    }
  }
  return vis;
}
function getPoss(clue){
  if(clue.join("")=="00"){
    return perms;
  }
  else if(clue[0]==0){
    return perms.filter(a=>getClue(a)[1]==clue[1]?a:false);
  }
  else if(clue[1]==0){
    return perms.filter(a=>getClue(a)[0]==clue[0]?a:false);
  }
  return perms.filter(a=>getClue(a).join("")==clue.join(""));
}
function guess(t,clues){
  let a = t.grid.indexOf(t.grid.find(e=>e.includes(0)));
  let temp = t.r[a].slice();
  
  for(var i = 0; i < temp.length; i++){
    t.r[a]=[temp[i]];
    
    try{
      t.runs = 0;
      t.apply();
      if(t.isSolved(t.grid)){
        return t;
      }
      if(t.grid.join("").includes(0)){
        t=guess(t, clues);
      }
    }
    catch(e){
      t=new Tower(clues); 
      t.apply();
    }
    finally{
      if(t.isSolved(t.grid)){
        return t;
      }
    }
    
    }
  return t;
}
function crossCheck(r,c){
  for(var i = 0; i < SIZE; i++){
    r[i]= r[i].filter(a=>a.every((e,j)=>c[j].find(b=>b[i]==e)));
  }
  
  return r; 
}
function filterPossible(possible, row, col, element){
  return possible.map((p,r)=>
                      p.filter(a=>r==row?a[col]==element:a[col]!=element)
                     );
}
function checkElement(e,i,poss){
  return poss.every(a=>a[i]==e)?e:false;
}
function rotateGrid(grid){
  let res = [];
  for(let i = 0; i < grid.length; i++){
    res.push(grid.map(e=>e[i]));
  }
  
  return res;
}

function generatePuzzle(p=[random(perms)]){
   if(p.length == PZ_SIZE){
     var c = rotateGrid(p);
     if(c.every(a=>a.slice().sort().join("")==values_str) && 
        p.every(a=>a.slice().sort().join("")==values_str)){
       var rc=[];
       var cc=[];
       for(var i = 0; i < PZ_SIZE; i++){
         rc.push(getClue(p[i]));
         cc.push(getClue(c[i]));
       }
       console.log(rc, cc)
       var res = [];
       res.push(cc.map(e=>e[0]));
       res.push(rc.map(e=>e[1]));
       cc=cc.reverse();
       rc=rc.reverse();
       res.push(cc.map(e=>e[1]))
       res.push(rc.map(e=>e[0]));
       
       return res.flat()
     }
     
   }
  var prm=shuffle(perms);
  var row = perms.find(a=>a.every((e,i)=>{
    for(var j of p){
     if(e == j[i]){return false}
    }
    return true;
  }));
 
  p.push(row);
 
 
  return generatePuzzle(p)
}