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
const (
	c7 =2;
	c8 int = 3;
	c88, c99 int = 88, 99;
	c9= "Florence";
	c10, c11, c12 = 7, true, "Florence"; 
)




func f() {
	fmt.Println("Florence") ;
}

func main() { 
	
	
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
	
	/*
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
	*/
	
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
	
	
	//test expression
	
	
	
}

var a1 int = 2




