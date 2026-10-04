#include<stdio.h>
void  powerset(char s[],char current[],int n,int index,int count){//宣告powerset函數 s是集合，current是目前選到的元素，n是有幾個元素，index是正在處理到第幾個元素，count是選了幾個元素
    if (index==n){//如果index=n代表全部元素處理完了
        printf("{");//因為完整輸出是{}所以要先輸出{
        for (int i=0;i<count;i++){
            printf ("%c",current[i]);//印出目前元素
            if (i<count-1){//代表還有元素還要處理
                printf(",");//不只輸出一個元素要用『,』隔開
            }
        }
        printf("}\n");//最後都處理完後輸出}
    }
    else{//代表還有沒處理完的元素
        powerset(s,current,n,index+1,count);//不選擇現在這個元素
        current[count]=s[index];//把目前的元素放入current
        powerset(s,current,n,index+1,count+1);//繼續處理下一個沒處理的元素
        }
    }
int main(){
    char s[]={'a','b','c'},current[10];//宣告s＝a,b,c current=10保留10個空間
    powerset(s,current,3,0,0);//呼叫s,current,3=三個元素,從第0個開始,現在選擇地0個元素
}