#include<iostream>
using namespace std;
int main();
class pack;
class staff;
class Client;// 包裹 客户 员工三大类提前声明 
struct running_account//记录交易流水的结构体
{ 
    string object_name;//交易名称
    double price;//运费
    string type_of_payment;//付款方式
    string pay_date;//付款日期
    bool ispaid;//用来判断是否付款的标记
};

class pack
{
 private:

  int pack_id;//本包裹的id 
  int id;//寄件人的id 
  string recipient;//收件人姓名 
  string recipient_contact;//收件人电话 
  string recipient_add;//收件人地址 
  string pick_add;
  int weight;//重量
  int price;//价格 
  int pack_state;//  包裹状态   0：公司尚未揽收； 1：以揽收，正在运送；2：已经签收尚未付款；3：已经签收，交易完成 
  string pick_time;//揽收时间
  string sign_time;//签收时间
  int  deliveryman;//送货员编号   0/1 
   
 public:
  friend class staff;
  friend class Client;//将员工与客户声明为包裹的友元 

  pack()
  {id=0;} //无参数的构造函数 
  pack(int f,int idd,string a,string b,string c,string d,string e);//含参构造函数 
  void display();//展示包裹信息 
};

pack::pack(int f,int idd,string a,string b,string c,string d,string e)
{
  pack_id=f;
  id=idd;
  recipient=a;
  recipient_contact=b;
  recipient_add=c;
  pick_add=e;
  pick_time=d;
  pack_state=0;   
}

void pack::display()//展示包裹信息
{
  cout<<"------------------------------------------------------------------------"<<endl;
  cout<<"包裹id为："<<pack_id<<endl;
  cout<<endl;
  cout<<"收件人姓名："<<recipient<<endl;
  cout<<endl;
  cout<<"收件人地址："<<recipient_add<<endl;
  cout<<endl;
  cout<<"收件人联系方式："<<recipient_contact<<endl;
  cout<<endl;
  switch(pack_state) //根据包裹状态不同输出不同的信息 
  {
   case(0):
    cout<<"公包裹目前状态：公司尚未揽收"<<endl;
    cout<<endl;
    break;
   case(1):
    cout<<"包裹重量："<<weight<<endl;
    cout<<endl;
    cout<<"包裹费用："<<price<<endl;
    cout<<endl;
    cout<<"包裹目前状态：已经揽收，正在运送"<<endl;
    cout<<endl;
    cout<<"送货员为";
    if(deliveryman==0)
     cout<<"张三"<<endl;
    else
     cout<<"李四"<<endl;
    break;
   case(2):
    cout<<"包裹重量："<<weight<<endl;
    cout<<endl;
    cout<<"包裹费用："<<price<<endl;
    cout<<endl;
    cout<<"包裹目前状态：已经签收,尚未付款"<<endl;
    cout<<endl;
    cout<<"送货员为";
    if(deliveryman==0)
    {
     cout<<"张三"<<endl;
    } 
       else
    {
      cout<<"李四"<<endl;
    }
    break;
   case(3):
    cout<<"包裹重量："<<weight<<endl;
    cout<<endl;
    cout<<"包裹费用："<<price<<endl;
    cout<<endl;
    cout<<"包裹目前状态：已经签收，交易完成"<<endl;
    cout<<endl;
    cout<<"送货员为";
    if(deliveryman==0)
    {
     cout<<"张三"<<endl;
    } 
    else
    {
     cout<<"李四"<<endl;
    }
    break;
  }
  cout<<"------------------------------------------------------------------------"<<endl;
}
pack obj_pack[100000];//可以容纳100000包裹的对象数组 

class Client//客户类 
{
 private:
   int ID;//客户id
        string name;//客户名字（可以是公司名字或是个人名字）
        string basic_address;//客户地址
        string contact_information;//联系方式
        running_account account[10000];//可以存放10000条交易流水的流水账
        int running_account_number;//记录流水账数目
        string password;
        int ownpack[100];//拥有包裹的id 
    public:
     friend void log_in();
  friend void id_register();
  friend void client_interface(int k);
  friend class pack;
     Client();
        Client(int id,string n,string add,string con,string m);//构造函数
        int operator ==(const int a);//重载运算符用于判断对象数组是否有元素 
  string get_name();//获得客户名称
        void add_running_account(string n,double p);//添加一条流水账
        void finish_running_account(string n, string fun,string d);//完成一条流水 n：交易名称 fun：交易方式 d：交易日期
        void show_running_account();//展示客户流水账
        void add_pack(int k);//添加包裹 
  void display_pack();//显示自己的包裹信息 
};
Client::Client()
{
    name="张三";
 basic_address="西安交通大学" ;
 contact_information="10000000";
 password=1111111;
}
Client::Client(int id,string n,string add,string con,string m)//构造函数
{
    ID=id;
    name=n;
    basic_address=add;
    contact_information=con;
    password=m;
    running_account_number=0;
 for(int jishu=0;jishu<=99;jishu++)
 {
  ownpack[jishu]=0;
 }
}

int Client::operator ==(const int a)//重载运算符用于判断对象数组是否有元素 
{
    if(name=="张三"&&contact_information=="10000000" )
    return 1;
    else
    return 0;
}

string Client::get_name()//获得客户名称
{
    return name;
}

void Client::add_running_account(string n,double p)//添加一条流水账
{
    account[running_account_number].object_name=n;
    account[running_account_number].price=p;
    account[running_account_number].ispaid=false;
    running_account_number++;
}

void Client::finish_running_account(string n, string fun,string d)//完成一条流水 n：交易名称 fun：交易方式 d：交易日期
{
    for(int i=0;i<running_account_number;i++)
     if(account[i].object_name==n)
            {
             account[i].ispaid=true;
                account[i].type_of_payment=fun;
                account[i].pay_date=d;
            }
}

void Client::show_running_account()//展示客户流水账
{
    for(int i=0;i<running_account_number;i++)
    {
        cout<<"交易名称："<<account[i].object_name<<" "<<"运费"<<account[i].price<<" ";
        if(account[i].ispaid==true)
            cout<<"付款日期："<<account[i].pay_date<<"付款方式："<<account[i].type_of_payment<<endl;
        else
            cout<<"未付款"<<endl;
    }
    cout<<"------------------------------------------------------------------------"<<endl;
    cout<<"共"<<running_account_number<<"条流水账"<<endl;  
}

void Client::add_pack(int k)//添加包裹 
{
    int pid;
    for(pid=1;pid<=100000;pid++)
    {
        if(obj_pack[pid].id==0)
        break;
 }
    string a;
 string b; 
    string c;
    string d;
    string e; 
    string delimiter;
    getline(cin,delimiter);
    cout<<"请输入收件人姓名："<<endl;
    getline(cin,a);
 cout<<endl;
    cout<<"请输入收件人联系方式："<<endl;
    getline(cin,b);
 cout<<endl;
    cout<<"请输入收件人地址："<<endl;
    getline(cin,c);
 cout<<endl;
    cout<<"请输入您期待的上门取货时间："<<endl;
    getline(cin,d);
 cout<<endl;
    cout<<"请输入您期待的取货地址："<<endl;
    getline(cin,e);
 cout<<endl;
    obj_pack[pid]=pack(pid,k,a,b,c,d,e);
    for(int y=0;y<=99;y++)
    {
        if(ownpack[y]==0)
        {
         ownpack[y]=pid;
         break;
  }
 }
 system("cls");
 cout<<"------------------------------------------------------------------------"<<endl;
 cout<<"添加包裹成功！"<<endl;
 cout<<"------------------------------------------------------------------------"<<endl;
 system("pause");
}

void Client::display_pack()//显示自己的包裹信息 
{
 for(int u=0;u<=99;u++)
 {
  if(ownpack[u]==0)
  {
   break;
  }
  else
  {
   obj_pack[ownpack[u]].display();
  }
 } 
}
Client obj[100];//可以容纳100客户的对象数组 

class staff
{
 public:
  staff(){}//无参构造函数 
  staff(int i,string a)//含参构造函数 
  {
   staffid=i;
   staff_password=a;
  }
  void staff_interface();//客户界面 
  void check_pack();//查看未揽收的包裹 
  void amend_pack(int i);//修改包裹信息 
  void check_ownpack();//查看自己负责的包裹 
  void add_running_tally();//添加流水 
  void close_deal();//完成交易 
  friend void log_in();
  friend int main();
 private:
  int staffid;//员工id 
  string staff_password;//员工密码，默认123456 
};
staff obj_staff[2];//两个员工的对象数组 

void staff::staff_interface()
{
 cout<<"------------------------------------------------------------------------"<<endl;
 cout<<"尊敬的员工，您好！"<<endl;
 cout<<endl;
 cout<<"请选择您想要执行的操作:"<<endl;
 cout<<endl;
 cout<<"查看未揽收的包裹           请输入1"<<endl;
 cout<<endl;
 cout<<"查看我负责运送的包裹       请输入2"<<endl;
 cout<<endl;
 cout<<"更新某个包裹的信息         请输入3"<<endl;
 cout<<endl;
 cout<<"为某一客户添加一条流水     请输入4"<<endl;
 cout<<endl;
 cout<<"为某一客户完成一条流水     请输入5"<<endl;
 cout<<endl;
 cout<<"退出程序                   请输入6"<<endl;
 cout<<"------------------------------------------------------------------------"<<endl;

 switch(getchar())
 {
  case('1'):
   system("cls");//清屏操作 system函数
   obj_staff[staffid].check_pack();
   system("cls");
   staff_interface();
  case('2'):
   system("cls");
   obj_staff[staffid].check_ownpack();
   system("cls");
   staff_interface();
  case('3'):
   system("cls");
   cout<<"请输入包裹id："<<endl;
   int k;
   cin>>k;
   obj_staff[staffid].amend_pack(k);
   system("cls");
   getchar();
   staff_interface();
  case('4'):
   system("cls");
   add_running_tally();
   system("cls");
   getchar();
   staff_interface(); 
  case('5'):
   system("cls");
   close_deal();
   system("cls");
   staff_interface(); 
  case('6'):
   system("cls");
   getchar();
   system("cls");
   main();
   break;
  default:
   system("cls");
   cout<<"输入错误 请输入正确的数字"<<endl;
   cout<<endl;
   cout<<endl;
   system("pause");
   staff_interface();
 } 
}

void staff::add_running_tally()
{
 cout<<"------------------------------------------------------------------------"<<endl;
 cout<<"请输入用户id"<<endl;
 int ki;
 cin>>ki;
 string a;
 cout<<"请输入该流水涉及的包裹id"<<endl;
 getchar();
 getline(cin,a);
 cout<<"请输入流水价钱"<<endl;
 double jiaqian;
 cin>>jiaqian;
 obj[ki].add_running_account(a,jiaqian);
 cout<<"------------------------------------------------------------------------"<<endl;
 system("cls");
 cout<<"------------------------------------------------------------------------"<<endl;
 cout<<"流水信息更新成功！"<<endl;
 cout<<"------------------------------------------------------------------------"<<endl;
 system("pause");
}
void staff::close_deal()
{
 cout<<"------------------------------------------------------------------------"<<endl;
 cout<<"请输入用户id"<<endl;
 int ki;
 cin>>ki;
 string a;
 string b;
 string c;
 cout<<"请输入包裹id"<<endl;
 getchar();
 getline(cin,a);
 cout<<"请输入交易方式"<<endl;
 getline(cin,b);
 cout<<"请输入交易日期"<<endl;
 getline(cin,c);
 obj[ki].finish_running_account(a,b,c);
 cout<<"------------------------------------------------------------------------"<<endl;
 system("cls");
 cout<<"------------------------------------------------------------------------"<<endl;
 cout<<"流水信息更新成功！"<<endl;
 cout<<"------------------------------------------------------------------------"<<endl;
 system("pause");
}
void staff::check_pack()
{
  system("cls");
  for(int i=1;i<=10000;i++)
  {
   if(obj_pack[i].id==0)
   {
   cout<<"------------------------------------------------------------------------"<<endl;
   cout<<"暂无包裹信息！"<<endl;
   cout<<"------------------------------------------------------------------------"<<endl;
   system("pause");
    break;
   }
   else
   {
    if(obj_pack[i].pack_state==0)
    {
     obj_pack[i].display();
    }
   }
  }  
  char c;
  getchar();
}
void staff::amend_pack(int i)
{
    system("cls");
   cout<<"------------------------------------------------------------------------"<<endl;
    cout<<"请选择您想要更新的数据:"<<endl;
    cout<<"包裹送货员  请输入1"<<endl;
   cout<<"包裹重量    请输入2"<<endl;
   cout<<"包裹状态    请输入3"<<endl;
   cout<<"包裹费用    请输入4"<<endl;
   cout<<"返回        请输入5"<<endl;
   cout<<"------------------------------------------------------------------------"<<endl;
   getchar();
   switch(getchar())
   {
    case('1'):
     cout<<"------------------------------------------------------------------------"<<endl;
     cout<<"请输入您的送货员id:"<<endl;
     cin>>obj_pack[i].deliveryman; 
     system("cls");
     cout<<"------------------------------------------------------------------------"<<endl;
     cout<<"数据更新成功！"<<endl;
     cout<<"------------------------------------------------------------------------"<<endl;
     system("pause");
     break; 
    case('2'):
     cout<<"------------------------------------------------------------------------"<<endl;
     cout<<"请输入包裹重量:"<<endl;
     cin>>obj_pack[i].weight;
     system("cls");
     cout<<"------------------------------------------------------------------------"<<endl;
     cout<<"数据更新成功！"<<endl;
     cout<<"------------------------------------------------------------------------"<<endl;
     system("pause");
     break;
    case('3'):
     cout<<"------------------------------------------------------------------------"<<endl;
     cout<<"请输入包裹新状态:"<<endl;
     cout<<"已揽收，正在运送   输入1"<<endl;
     cout<<"已签收，未付款   输入2"<<endl;
     cout<<"已签收，交易完成 输入3"<<endl;
     cout<<"------------------------------------------------------------------------"<<endl;
     cin>>obj_pack[i].pack_state; 
     if(obj_pack[i].pack_state==1)
     {
      string delimiter;
      cout<<"------------------------------------------------------------------------"<<endl;
      cout<<"请输入揽收时间:"<<endl;
      getline(cin,delimiter);
      getline(cin,obj_pack[i].pick_time);
     }
     else
     {
      if(obj_pack[i].pack_state==2)
      {
       string delimiter1;
       cout<<"------------------------------------------------------------------------"<<endl;
       cout<<"请输入签收时间:"<<endl;
       getline(cin,delimiter1);
       getline(cin,obj_pack[i].sign_time);
      }
      else
      {getchar();} 
     } 
     system("cls");
     cout<<"------------------------------------------------------------------------"<<endl;
     cout<<"数据更新成功！"<<endl;
     cout<<"------------------------------------------------------------------------"<<endl;
     system("pause");
     break;
    case('4'):
     cout<<"------------------------------------------------------------------------"<<endl;
     cout<<"请输入包裹费用:"<<endl;
     cin>>obj_pack[i].price;
     system("cls");
     cout<<"------------------------------------------------------------------------"<<endl;
     cout<<"数据更新成功！"<<endl;
     cout<<"------------------------------------------------------------------------"<<endl;
     system("pause"); 
     break;
    case('5'):
     amend_pack(i);
    default:
     system("cls");
     cout<<"------------------------------------------------------------------------"<<endl;
     cout<<"命令无效 请输入正确的数字"<<endl;
     cout<<"------------------------------------------------------------------------"<<endl;
     system("pause");
   } 
   
}
void staff::check_ownpack()
{
  system("cls");
  for(int i=1;i<=10000;i++)
  {
   if(obj_pack[i].id==0)
   {
   cout<<"------------------------------------------------------------------------"<<endl;
   cout<<"暂无包裹信息！"<<endl;
   cout<<"------------------------------------------------------------------------"<<endl;
   system("pause");
    break;
   }
   else
   {
    if(obj_pack[i].deliveryman==staffid)
    {
     obj_pack[i].display();
    }
   }
  }  
  getchar();
}

void client_interface(int k)//客户主界面 
{
 cout<<"------------------------------------------------------------------------"<<endl;
 cout<<"尊敬的客户，您好！"<<endl;
 cout<<endl;
 cout<<"请选择您想要执行的操作:"<<endl;
 cout<<endl;
 cout<<"我要寄件           请输入1"<<endl;
 cout<<endl;
 cout<<"查看正在运送的包裹 请输入2"<<endl;
 cout<<endl;
 cout<<"查看我的账单       请输入3"<<endl;
 cout<<endl;
 cout<<"退出程序           请输入4"<<endl;
 cout<<"------------------------------------------------------------------------"<<endl;
 switch(getchar())
 {
  case('1'):
   system("cls");
   obj[k].add_pack(k);
   client_interface(k);
  case('2'):
   system("cls");
   obj[k].display_pack();
   getchar();
   client_interface(k);
  case('3'):
   system("cls");
   obj[k].show_running_account();
   getchar();
   client_interface(k);
  case('4'):
   system("cls");
   getchar();
   main();
   break;
  default:
   system("cls");
   cout<<"------------------------------------------------------------------------"<<endl;
   cout<<"命令无效 请输入正确的数字"<<endl;
   cout<<"------------------------------------------------------------------------"<<endl;
   system("pause");

  } 
}
void log_in ()//登录界面 
{
 system("cls");
 cout<<"------------------------------------------------------------------------"<<endl;
 cout<<"请输入您的ID："<<endl;
 int id;
 string delimiter;
 string mima; 
 cin>>id;
 getline(cin,delimiter);
 cout<<"请输入您的密码："<<endl;
 getline(cin,mima);
 if(obj[id].password==mima)
 {
  system("cls");
  client_interface(id);
 }
 else
 {
 if(obj_staff[id].staff_password==mima)
  {
   system("cls");
   obj_staff[id].staff_interface();
  }
  else
  {
   system("cls");
   cout<<"------------------------------------------------------------------------"<<endl;
   cout<<"ID或密码错误，请重新登录"<<endl;
   cout<<"------------------------------------------------------------------------"<<endl;
   system("pause");

   main(); 
  }
 }
 
}
void id_register()//用户注册界面 
{
 string delimiter;
 string name;
 string address;
 string contact;
 string password1; 
 system("cls");
 cout<<"------------------------------------------------------------------------"<<endl;
 getline(cin,delimiter);
 cout<<"请输入您的姓名："<<endl;
 getline(cin,name);
 cout<<endl; 
 cout<<"请输入您的住址："<<endl;
 getline(cin,address);
 cout<<endl;
 cout<<"请输入您的电话号码："<<endl;
 getline(cin,contact);
 cout<<endl;
 cout<<"请设置您的密码："<<endl;
 getline(cin,password1);
 int i=2;
 for(i=2;i<100;i++)
 {
  if(obj[i]==0)
  {
   obj[i]=Client(i,name,address,contact,password1);
   break;
  }
  
 }
 system("cls");
 cout<<"------------------------------------------------------------------------"<<endl;
 cout<<"注册成功!您的ID是："<<i<<endl; 
 cout<<endl;
 cout<<"请重新登录"<<endl; 
 cout<<"------------------------------------------------------------------------"<<endl;
 system("pause");
 log_in ();
} 

int main()//主函数 
{
 obj_staff[0].staffid=1;
 obj_staff[1].staffid=1;
 obj_staff[0].staff_password="123456";
 obj_staff[1].staff_password="123456";
 cout<<"------------------------------------------------------------------------"<<endl;
 cout<<"欢迎来到无敌螺旋物流!!!"<<endl;
 cout<<endl;
 cout<<"请选择您想要执行的操作:"<<endl;
 cout<<endl;
 cout<<"登录已有帐号  请输入1"<<endl;
 cout<<endl;
 cout<<"注册账号      请输入2"<<endl;
 cout<<endl;
 cout<<"                                                              版本v1.0.2"<<endl;
 cout<<"                                     版权所有：XJTU 高浩翔 施炎江 薛杰锋"<<endl;
 cout<<"------------------------------------------------------------------------"<<endl;
   
 switch(getchar())
 {
  case('1'):
   log_in(); 
   break;
  case('2'):
   id_register();
   break;
  default:
   system("cls");
   cout<<"------------------------------------------------------------------------"<<endl;
   cout<<"命令无效 请输入正确的数字"<<endl;
   cout<<"------------------------------------------------------------------------"<<endl;
   system("pause");
   main();
  } 
  return 0;
}
