awk
BEGIN{
 FS=","
 print "Name\t\t\tSRN\t\tOS\tSP\tCN\tPM\tWT\tOVR"
}
FNR>0{
 if($3>90){ grade1="O" }
 else if($3>80){ grade1="A+" }
 else if($3>70){ grade1="A" }
 else if($3>60){ grade1="B+" }
 else if($3>50){ grade1="B" }
 else if($3>40){ grade1="P"}
 else{grade1="F"}
 if($4>90){ grade2="O" }
 else if($4>80){ grade2="A+" }
 else if($4>70){ grade2="A" }
 else if($4>60){ grade2="B+" }
 else if($4>50){ grade2="B" }
 else if($4>40){ grade2="P"}
 else{grade2="F"}
 if($5>90){ grade3="O" }
 else if($5>80){ grade3="A+" }
 else if($5>70){ grade3="A" }
 else if($5>60){ grade3="B+" }
 else if($5>50){ grade3="B" }
 else if($5>40){ grade3="P"}
 else{grade3="F"}
 if($6>90){ grade4="O" }
 else if($6>80){ grade4="A+" }
 else if($6>70){ grade4="A" }
 else if($6>60){ grade4="B+" }
 else if($6>50){ grade4="B" }
 else if($6>40){ grade4="P"}
 else{grade4="F"}
 
 if($7>90){ grade5="O" }
 else if($7>80){ grade5="A+" }
 else if($7>70){ grade5="A" }
 else if($7>60){ grade5="B+" }
 else if($7>50){ grade5="B" }
 else if($7>40){ grade5="P"}
 else{grade5="F"}
 
 ovr=($3+$4+$5+$6+$7)/5
 if(ovr>90){ grade6="O" }
 else if(ovr>80){ grade6="A+" }
 else if(ovr>70){ grade6="A" }
 else if(ovr>60){ grade6="B+" }
 else if(ovr>50){ grade6="B" }
 else if(ovr>40){ grade6="P"}
 else{grade6="F"}
 if(grade1=="F"||grade2=="F"||grade3=="F"||grade4=="F"||grade5=="F"){grade6="F"}
 print $1,"\t",$2,"\t\t",grade1,"\t",grade2,"\t",grade3,"\t",grade4,"\t",grade5,"\t",grade6
}