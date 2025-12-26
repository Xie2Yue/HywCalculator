#ifndef _XIE2YUE_GRAPH_H
#define _XIE2YUE_GRAPH_H

/*

必须重构！！！
自己都看不下去了
T_T


*/

#include <set>
#include <random>
#include <iostream>
#include <functional>


#define ll long long
#define uint unsigned int


struct Node{
	uint pry, data, siz;
	Node *ls, *rs, *ft;
	Node(uint data): data(data), siz(1), pry(rand()), ls(nullptr), rs(nullptr), ft(nullptr) {}
};

class Treap{
	
	private:
		
	void updateSize(Node *p) {
		if(p != nullptr) {
			p->siz = 1;
			p->siz += (p->ls != nullptr ? p->ls->siz : 0);
			p->siz += (p->rs != nullptr ? p->rs->siz : 0);
		}
	}
	
	public:
		
	Node *root = nullptr;
	
	Node* newNode(uint v) {
		return new Node(v);
	}
	// 特殊二分查找
	void split(Node *p,uint rp,Node *&l, Node *&r) {
		
	    l = r = nullptr;
	    Node *lt = nullptr, *rt = nullptr, *pt = nullptr;
	    uint pos = 0;
	    
	    while (p) {
	    	
	        uint left_size = p->ls ? p->ls->siz : 0;
	        uint mid = pos + left_size;
	        
	        if (p->data - mid <= rp) {
	        	
	            if (!lt) {
	            	l = lt = p;
		            p = p->rs;
		            lt->rs = nullptr;
		            if(p) p->ft = nullptr;
				}
	            else {
	            	pt = p->rs;
	            	p->rs = nullptr;
	            	if(pt) pt->ft = nullptr;
	            	lt->rs = p;
	            	p->ft = lt;
	            	lt = lt->rs;
	            	p = pt;
				}
		    	pos = mid + 1;
		    	
	        } else {
	        	
	            if (!rt) {
	            	r = rt = p;
		            p = p->ls;
		            rt->ls = nullptr;
		            if(p) p->ft = nullptr;
				}
	            else {
	            	pt = p->ls;
	            	p->ls = nullptr;
	            	if(pt) pt->ft = nullptr;
	            	rt->ls = p;
	            	p->ft = rt;
	            	rt = rt->ls;
	            	p = pt;
				}
				
	        }
	    }
	    while(lt){
	    	
	    	updateSize(lt);
	    	lt = lt->ft;
	    	
		}
		while(rt){
			
			updateSize(rt);
			rt = rt->ft;
			
		}
	}
	// 插入已存在数据的普通二分查找
	uint splitVal(Node *p,uint rp,Node *&l, Node *&r) {
		
	    l = r = nullptr;
	    Node *lt = nullptr, *rt = nullptr, *pt = nullptr;
	    
	    while (p) {
	        
	        if (p->data <= rp) {
	        	
	            if (!lt) {
	            	l = lt = p;
		            p = p->rs;
		            lt->rs = nullptr;
		            if(p) p->ft = nullptr;
				}
	            else {
	            	pt = p->rs;
	            	p->rs = nullptr;
	            	if(pt) pt->ft = nullptr;
	            	lt->rs = p;
	            	p->ft = lt;
	            	lt = lt->rs;
	            	p = pt;
				}
				
	        } else {
	        	
	            if (!rt) {
	            	r = rt = p;
		            p = p->ls;
		            rt->ls = nullptr;
		            if(p) p->ft = nullptr;
				}
	            else {
	            	pt = p->ls;
	            	p->ls = nullptr;
	            	if(pt) pt->ft = nullptr;
	            	rt->ls = p;
	            	p->ft = rt;
	            	rt = rt->ls;
	            	p = pt;
				}
				
	        }
	    }
	    
	    uint ret = -1;
	    
	    while(lt){
	    	
	    	if(ret == -1) ret = lt->data;
	    	
	    	updateSize(lt);
	    	lt = lt->ft;
	    	
		}
		while(rt){
			
			updateSize(rt);
			rt = rt->ft;
			
		}
		
		return ret;
		
	}
	// 瞎写的
	uint splitVal(Node *p,uint rp,Node *&l, Node *&r, std::function<bool(const ll&, const Node&)> cmp) {
		
	    l = r = nullptr;
	    Node *lt = nullptr, *rt = nullptr, *pt = nullptr;
	    
	    while (p) {
	        
	        if (cmp(rp, *p)) {
	        	
	            if (!lt) {
	            	l = lt = p;
		            p = p->rs;
		            lt->rs = nullptr;
		            if(p) p->ft = nullptr;
				}
	            else {
	            	pt = p->rs;
	            	p->rs = nullptr;
	            	if(pt) pt->ft = nullptr;
	            	lt->rs = p;
	            	p->ft = lt;
	            	lt = lt->rs;
	            	p = pt;
				}
				
	        } else {
	        	
	            if (!rt) {
	            	r = rt = p;
		            p = p->ls;
		            rt->ls = nullptr;
		            if(p) p->ft = nullptr;
				}
	            else {
	            	pt = p->ls;
	            	p->ls = nullptr;
	            	if(pt) pt->ft = nullptr;
	            	rt->ls = p;
	            	p->ft = rt;
	            	rt = rt->ls;
	            	p = pt;
				}
				
	        }
	    }
	    
	    uint ret = -1;
	    
	    while(lt){
	    	
	    	if(ret != -1) ret = lt->data;
	    	
	    	updateSize(lt);
	    	lt = lt->ft;
	    	
		}
		while(rt){
			
			updateSize(rt);
			rt = rt->ft;
			
		}
		
		return ret;
		
	}
	// 合并
	Node* merge(Node *l, Node *r) {
		
		// 丑陋至极！
		if(!l) return r;
		if(!r) return l;
		
		Node *ret = nullptr, *p = nullptr, *pt = nullptr;
		bool pd = 0;
		
		while(l != nullptr && r != nullptr) {
			
			if(l->pry < r->pry) std::swap(l, r);
			
			l->siz += r->siz;
			
			if(l->data < r->data) {
				
				if(!ret) {
					
					p = ret = l;
					l = l->rs;
					p->rs = nullptr;
					if(l) l->ft = nullptr;
					pd = 1;
					
				} else {
					
					pt = l;
					l = l->rs;
					pt->rs = nullptr;
					if(l) l->ft = nullptr;
					if(pd) {
						p->rs = pt;
					} else {
						p->ls = pt;
					}
					if(pt) pt->ft = p;
					p = pt;
					pd = 1;
					
				}
				
			} else {
				
				if(!ret) {
					
					p = ret = l;
					l = l->ls;
					p->ls = nullptr;
					if(l) l->ft = nullptr;
					pd = 0;
					
				} else {
					
					pt = l;
					l = l->ls;
					pt->ls = nullptr;
					if(l) l->ft = nullptr;
					if(pd) {
						p->rs = pt;
					} else {
						p->ls = pt;
					}
					if(pt) pt->ft = p;
					p = pt;
					pd = 0;
					
				}
				
			}
			
		}
		
		if(!l) {
			
			if(pd) {
				p->rs = r;
			} else {
				p->ls = r;
			}
			
			r->ft = p;
			
		} else {
			
			if(pd) {
				p->rs = l;
			} else {
				p->ls = l;
			}
			
			l->ft = p;
			
		}
		
		return ret;
		
	}
	
	void print(Node*p) const{
		if(!p)return;
		print(p->ls);
		std::cout<<p->data<<"\n";
		print(p->rs);
	}
	
	void print() const {print(root);}
	
	void clear(Node*p){
		if(p==nullptr)return;
		clear(p->ls);
		clear(p->rs);
		delete p;
	}
	
	void clear(){
		if(root==nullptr)return;
		clear(root);
		root=nullptr;
	}
	
	uint getMax(Node *p) const {// 调试用，获得搜索树的最大值
		if(p == nullptr) return -1;
		Node *cur;
		cur = p;
		while(cur->rs != nullptr) {
			cur = cur->rs;
		}
		return cur->data;
	}
	
};


//------------------------------------------------------------------------------------


class Graph {
	
	private:
		
	uint idx = 0;
	
	struct Edge {
		
		uint to;
		
		mutable int weight;
		
		Edge(uint v, ll w): to(v), weight(w) {}
		
	};
	
	class Vertex {
		
		private:
			
		uint _id;
		std::vector<Edge> _outEdges;
		
		public:
		
		Vertex(uint id): _id(id) {}
		
		uint getId() const { return _id; }
		
		void addEdge(uint to, ll weight=0) {
			
			_outEdges.emplace_back(to, weight);
			
		}
		
		const std::vector<Edge>& getEdges() const {
			
			return _outEdges;
			
		}
		
	};
	
	std::vector<Vertex> V;
	
	uint E=0;
	
	public:
	
	uint VertexSize() const { return V.size(); }
	
	uint EdgeSize() const { return E; }
	
	uint addVertex() {
		
		V.emplace_back(idx);
		
		return idx++;
		
	}
	
	void addEdge(uint u, uint v, ll weight = 0) {
		// 调试用，并不会触发
		if(u == v || u >= V.size() || v >= V.size()) {
			
			std::cout<<"Error\n"<<u<<" "<<v<<" "<<V.size()<<"\nError\n";
			
			return;
			
		}
		
		V[u].addEdge(v, weight);
		
		++E;
		
	}
	
	void clear() {
		
		V.clear();
		idx = 0;
		E = 0;
		
	}
	
	
	void createRandomGraph(uint n, uint m) {
		// 随机生成一个有向图，采用 Floyd 采样保证随机
		
		if(n <= 1) return;
		if(m > n * (n - 1)) m = n * (n - 1);
		if(m < n - 1) m = n - 1 ;
		
		clear();
		
		std::set<uint>S;
		static std::random_device rd;
		static std::mt19937 gen(rd());
		
		for(int i = 0; i < n; ++i) {
			addVertex();
		}
		
		for(int i = n * (n - 1) - m; i < n * (n - 1); ++i) {
			if( i <= 1) {
				S.insert(i);
				continue;
			}
			std::uniform_int_distribution<> dis(0, i - 1);
			uint val = dis(gen);
			if(S.count(val)) {
				S.insert(i);
			} else {
				S.insert(val);
			}
			
		}
		
		for(const auto& pr: S) {
			
			uint v = pr / (n - 1);
			uint u = pr % (n - 1);
			u += u >= v;
			addEdge(u, v);
			
		}
		
	}
	
	
	void createRandomSingleSourceFullConnectedGraph1(uint n, uint m) {
		// 随机生成一个图，满足从 0 号点出发可以到达所有节点
		// 实现代码和 addNewRandomEdge 差不多不做过多注释
		if(n <= 1) return;
		if(m > n * (n - 1)) m = n * (n - 1);
		if(m < n - 1) m = n - 1 ;
		
		clear();
		
		Treap edgeIndex;
		Node *l, *r;
		static std::random_device rd;
		static std::mt19937 gen(rd());
		
		// 加入 n 个点
		for(uint i = 0; i < n; ++i) {
			addVertex();
		}
		// 生成一个以 0 为根的生成树
		for(uint i = 1; i < n; ++i) {
			
			std::uniform_int_distribution<> dis(0, i - 1);
			uint val = dis(gen) + i * (n - 1);
			
			// Treap排序插入
			edgeIndex.splitVal(edgeIndex.root, val, l, r);
			edgeIndex.root=edgeIndex.merge(edgeIndex.merge(l, edgeIndex.newNode(val)), r);
		}
		
		// 核心
		// 通过Treap直接略过已经存在的数据
		for(uint i = n; i <= m; ++i) {
			
			std::uniform_int_distribution<> dis(0 , n * (n - 1) - i);
			uint rp = dis(gen);
			
			// Treap特殊插入
			edgeIndex.split(edgeIndex.root, rp, l, r);
			
			
			// 注释掉的这一段是可拓展化，但是速度有些慢
			// 但是还是我好不容易写出来的，所以就留下来吧
//			uint pos = 0;
//			edgeIndex.splitVal(edgeIndex.root, rp, l, r, [&pos](const ll& val, const Node& p){
////				static uint pos = 0;
//				static uint left_size = 0;
//				left_size = p.ls ? p.ls->siz : 0;
//				if(p.data - pos - left_size <= val) {
//					pos += left_size + 1;
//					return 1;
//				}
//				return 0;
//			});

			edgeIndex.root=edgeIndex.merge(edgeIndex.merge(l, edgeIndex.newNode(rp + (l ? l->siz : 0 ))), r);
			
		}
		
		// 清空Treap并添加所有边
		auto clr = [n, this](Node *p,auto self) -> void {
			
			if(p == nullptr) return;
			self(p->ls, self);
			self(p->rs, self);
			uint v = p->data / (n - 1);
			uint u = p->data % (n - 1);
			u += u >= v;
			addEdge(u, v);
			delete p;
			
		};
		
		Node* toClr = edgeIndex.root;
		edgeIndex.root=nullptr;
		clr(toClr, clr);
		
	}
	
	void addNewRandomEdges(int m) {
		// @功能
		// 向现有的图中添加边
		// @ 问题
		// 由于现有的图已经存在了一些边，那么采样算法就要实现在已经存在一些数据的情况下，从 [0,n) 中生成若干个数
		// 如果使用拒绝采样，在边比较满的情况下是指数级别的，非常不优
		// 于是采用了自己设计的随机采样算法和自己稍微修改的数据结构
		// @思想
		// 使用二叉搜索树(这里是 Treap)管理已存在的数据
		// 在采样阶段，不关注存在的数据究竟是什么，只返回将要生成的数在未生成数据中的排名 rp
		// 在通过二叉搜索树二分查找将要生成的数 num， 其满足 num = rp + size，其中 size 为小于 num 的已生成数据数
		
		// 边界条件
		if(m < 1) return;
		auto n = V.size();
		auto Epi = E;
		if(m + E > n * (n - 1)) m = n * (n - 1) - E;
		
		
		Treap edgeIndex;
		Node *l, *r;
		static std::random_device rd;
		static std::mt19937 gen(rd());
		
		// 向二叉搜索树中插入现有边
		for(uint u = 0; u < n; ++u) {
			for(auto [v, w] : V[u].getEdges()) {
				
				// 边的编码方式，主要是为了去掉自环的编码
				uint val = u + v * (n - 1) - (u > v);
				
				edgeIndex.splitVal(edgeIndex.root, val, l, r);
				edgeIndex.root=edgeIndex.merge(edgeIndex.merge(l, edgeIndex.newNode(val)), r);
			}
		}
		
		// 重置整个图，因为存储原有边的花费和重新插入的花费差不多
		clear();
		
		for(uint i = 0; i < n; ++i) {
			addVertex();
		}
		
		for(uint i = 1; i <= m; ++i) {
			
			// 生成排名 rp
			std::uniform_int_distribution<> dis(0 , n * (n - 1) - i - Epi);
			uint rp = dis(gen);
			
			// 二分查找并插入
			edgeIndex.split(edgeIndex.root, rp, l, r);

			edgeIndex.root=edgeIndex.merge(edgeIndex.merge(l, edgeIndex.newNode(rp + (l ? l->siz : 0 ))), r);
			
		}
		
		// 重新插入边并删除指针
		auto clr = [n, this](Node *p,auto self) -> void {
			
			if(p == nullptr) return;
			self(p->ls, self);
			self(p->rs, self);
			// 逆编码
			uint v = p->data / (n - 1);
			uint u = p->data % (n - 1);
			u += u >= v;
			addEdge(u, v);
			delete p;
			
		};
		
		Node* toClr = edgeIndex.root;
		edgeIndex.root=nullptr;
		clr(toClr, clr);
		
	}
	
	friend std::istream& operator >> (std::istream &in, Graph &t) {
		
		static uint Gbuf = 0, inu = 0, inv = 0, inw = 0;
		
		in >> Gbuf;
		
		for(int i = 0; i < Gbuf ; ++i) {
			t.addVertex();
		}
		
		in >> Gbuf;
		
		for(int i = 0; i < Gbuf ; ++i) {
			in >> inu >> inv >> inw;
			t.addEdge(inu, inv, inw);
		}
		
		return in;
		
	}
	
	friend std::ostream& operator << (std::ostream &out, Graph t) {
		
		out << t.V.size() << " " << t.E << "\n";
		
		for(int i = 0; i < t.V.size(); ++i) {
			for(auto [v, w] : t.V[i].getEdges()) {
				out << t.V[i].getId() << " " << v << " " << w <<"\n";
			}
		}
		
		return out;
		
	}

};


#undef ll
#undef uint
#endif