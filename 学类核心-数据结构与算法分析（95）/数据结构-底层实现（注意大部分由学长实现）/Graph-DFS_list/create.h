#include<iostream>
#define LINELEN 80
using namespace std;

char* getl(char* buffer, int n, FILE* fid) {
  char* ptr;
  ptr = fgets(buffer, n, fid);
  while ((ptr != NULL) && (buffer[0] == '#'))
    ptr = fgets(buffer, n, fid);
  return ptr;
}
/*
构建图
*/ 
//template <typename GType>
Graph<string>* createGraph(	FILE* fid) {
  char buffer[LINELEN+1]; // Line buffer for reading
  int i, v1, v2, dist;

	/*【读取顶点个数】 */
  if (getl(buffer, LINELEN, fid) == NULL) // Unable to get number of vertices
	{ cout << "Unable to read number of vertices\n";
    return NULL;
	}
	int num=atoi(buffer);
	/*【建图初始化】 */
  Graph<string>* G = new Graphl<string>(num);

	
	/*【读取图的顶点信息并存储】 */
  if (getl(buffer, LINELEN, fid) == NULL) // Unable to get graph type
	{ cout << "Unable to read info of vertices\n";
    return NULL ;
	}
	char* cbuff=buffer;

	string ver=strtok(cbuff," ");//空格分割各顶点信息 
	//存储前n-1个 
	for(i=0;i<num-1;i++){
		G->putVex(i,ver);//存储顶点信息 
		ver=strtok(NULL," ");
	} 
	//最后一个顶点信息之后的字符可能是\t之类的字符故不能和上面一样
	//直接用空格分割 
	int k=0;
	while(ver[k]>=33&&ver[k]<=126){
		k++;
	}
	ver=ver.substr(0,k);//获取最后一个顶点信息 
	G->putVex(i,ver);//存储顶点信息 
	
	/*【读取图的类型】 */
  if (getl(buffer, LINELEN, fid) == NULL) // Unable to get graph type
	{ cout << "Unable to read graph type\n";
    return NULL ;
	}
  if (buffer[0] == 'U')//无向图 
    G->setType(true);//undirected = true;
  else if (buffer[0] == 'D')//有向图 
    G->setType(false);//undirected = false;
  else {
    cout << "Bad graph type: |" << buffer << "|\n";
    return NULL;
  }

  /*【读取边数和边】 */
  if (getl(buffer, LINELEN, fid) == NULL) // Unable to get graph type
	{ cout << "Unable to read num of edges\n";
    return NULL ;
	}
	int num_edge=atoi(buffer);
  for(int m=0;m<num_edge;m++){
  	getl(buffer, LINELEN, fid);
  	string sbuff=buffer;
  	string tvalue;
  	
  	int loc1=sbuff.find(' ');//找到第一个分割空格的位置 
  	tvalue=sbuff.substr(0,loc1);//读取第一个顶点信息到tvalue 
  	//cout<<"第一个顶点" <<tvalue<<endl;////////////
  	//找到第一个顶点在图中的位置
  	v1 = G->locateVex(tvalue);
		int loc2=sbuff.find(' ',loc1+1);//找第二个分割空格的位置 

  	tvalue=sbuff.substr(loc1+1,loc2-loc1-1);//读取第二个顶点信息到tvalue 
  	//cout<<"第二个顶点" <<tvalue<<endl;////////////
		//找到第二个顶点在图中的位置
		v2 = G->locateVex(tvalue);
   	//获取dist边权值 
   	i=loc2+1;
   	dist=atoi(&buffer[i]);
		//cout<<"dist="<<dist<<endl; 
		//存储边
		G->setEdge(v1,v2,dist); 
  }
  return G;
}

/*打印图*/ 
void Gprint(Graph<string>* G) {
  int i, j;
  cout << "顶点数：" << G->n() << "\n";
  cout << "边  数: " << G->e() << "\n";
	cout << "图类型: "<<(G->getType()?"无向图":"有向图")<<endl; 
	cout << "顶点信息：\n";
	for(i=0;i<G->n();i++){
		cout<<G->getVex(i)<<"  ";
	} 
	cout<<endl;
  cout<<"边信息：\n";
  if(G->getType()){
  	for (i=0; i<G->n(); i++) {
	    for(j=i; j<G->n(); j++){
	    	if(G->weight(i, j)!=0){
	    		cout<<G->getVex(i)<<" <--> "<<G->getVex(j)<<":"<<G->weight(i, j)<<endl;
				}
			}
  	}
	} 
	else{
		for (i=0; i<G->n(); i++) {
	    for(j=0; j<G->n(); j++){
	    	if(G->weight(i, j)!=0){
	    		cout<<G->getVex(i)<<" --> "<<G->getVex(j)<<":"<<G->weight(i, j)<<endl;
				}
			}
  	}
	}
    cout << "邻接表为:\n";
    int v,w;
    for(v=0;v<G->n();v++){
      cout<<G->getVex(v);
      for(w=G->first(v);w<G->n();w = G->next(v,w)){
        cout<<" --> "<<G->getVex(w);
      }
    cout<<endl;
    } 
}
