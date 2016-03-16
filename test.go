package main

import "fmt"
import "flag"
import (
	"go/ast";
	"log";
	"net/http";
)

var v1 =2
var v2 int = 3
var v3= "Florence"
var v4, v5, v6 = 7, true, "Florence" 
var (
)

var (
	v7 =2;
	v8 int = 3;
	v9= "Florence";
	v10, v11, v12 = 7, true, "Florence"; 
)

const c1 =2
const v2 int = 3
const v3= "Florence"
const v4, v5, v6 = 7, true, "Florence" 
const (
)

func f() {
	fmt.Println("Florence") ;
}

func f2 (a int, b string, c float32) int {
	return 1 ; 
}

func f3 (a int, b string, c float32) () {
	 
}

func f4 (a int, b string, c float32) (int) {
	return 1; 
}

func f1 (a int, b string, c float32) (a, b, c int, str string, arr [32] int) {
	return 1 ; 
}

func function_with_nobody() 

func main() { 
	
	var e1, e2, e3, e4, e5, e6 int ; 
	e1;
	true; 
	false ; 
	"TEST";
	1.2 ; 
	3; 
	e1++; 
	e1--; 
	e1 += e2; 
	e1 -= e2; 
	e1 *= e2; 
	e1 /= e2; 
	e1, e2 = e3, e4; 
	e1, e2 = 1, 2 ; 
	e1 = true; 
	e2 = false; 
	e1 = 1.3 ; 
	e1 = "Florence"; 
	e1 = e3 ; 
	e1 = 5; 
	e1 = (e2); 
	var arr [10] int ; 
	arr[e2] = 5; 
	f1(e3, e4, e5) ; 
	
	e1 = true;
	e1 = -5 ;
	e2 = +5; 
	
	e1 && e2 || e3;
	e1 == e4;
	e2 != e5; 
	e1 >=  32 ;

	(e1+5 * e3)/e4  > -e3 +1 ; 

	e1 + e2 + e3 + e5 + e5 +
		e6 % e7; 

	((f1() +1 ) * 10 - f2(1,2,3)/4 + 2) % (-5 + 7*e4 - e4 * e5 * (e6 -e7)) || e6 && true;

	(1+ (e2 - (-e3 + (e4 % (e5-1)))) - ((((arr[7]))))) == 100 + "test";

	//array
	var x[5] int;
	var i int = 0; 
	
	
	//branch
	var a int  = 6;
	if a%2 == 0 {
		fmt.Println(a , " is even");
	}else  {
		fmt.Println(a, " is odd");
	};
	
	var max = 10 ;  
	if a  = 11; a > max {
		fmt.Println("Greater");
	}else if (a == max){
		fmt.Println("Equal");
	}else {
		fmt.Println("Less than"); 
	}
	;
	
	if (true == false) {
		fmt.Println("The apocalypse"); 
	};
	
	//empty block
	if (true != false) {
	};
	
	//branch
	var str string = "student";
	switch str {
		case "student":
			fmt.Println("Go to lecture"); 
		case "Employer":
			fmt.Println("Go get some beer");
		default:
			fmt.Println("Go get fun");  	
	};
	
	var t1  int = 0 ; 
	
	switch {
		case t1 == 0:
			fmt.Println("Go to lecture"); 
		case t1 == 1:
			fmt.Println("Go get some beer");
		default:
			fmt.Println("Go get fun");  	
	};
	
	var t2 int; 
	var t3 int = 3; 
	switch t2=3; t3{
		case 3:
			fmt.Println("Go to lecture"); 
		case 4:
			fmt.Println("Go get some beer");
		default:
			fmt.Println("Go get fun");  	
	};
	
	switch str = "student"; {
		case t3 ==1:
			fmt.Println("Go to lecture"); 
		case t3 ==2:
			fmt.Println("Go get some beer");
		default:
			fmt.Println("Go get fun");  	
	};
	
	//cycle 
	i = 0; 
	for i < 3 {
		i +=1; 
		fmt.Println(i); 
	};
	
	var j int =0;
	
	
	for i<1  {
		x[i] = 1;
		i=2;
	};
	
	//for i == 1; i < 2 ;  {
	//	x[i] = 1;
	//}
	
	for  ; j  < 5 ; j++ {
		fmt.Println(j) ;
		continue;
	};
	
	for {
		fmt.Println("Loop");
		break; 
	};
	
	
	//input output by console
	/*
	fmt.Println("Input a number");
	var number int; 
	fmt.Scanln(&number); 
	fmt.Println(number); 
	
	fmt.Println("Input a string");
	var inputStr string; 
	fmt.Scanln(&inputStr); 
	fmt.Println(inputStr); 
	
	fmt.Println("Input a boolean value");
	var boolVal bool; 
	fmt.Scanln(&boolVal); 
	fmt.Println(boolVal); 
	
	fmt.Println("Input a float value");
	var floatVal float32; 
	fmt.Scanln(&floatVal); 
	fmt.Println(floatVal); 
	*/
	
}

const (
	c7 =2;
	c8 int = 3;
	c88, c99 int = 88, 99;
	c9= "Florence";
	c10, c11, c12 = 7, true, "Florence"; 
)

var a1 int = 2




