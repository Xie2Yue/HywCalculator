#ifndef _XIE2YUE_GRAPH_H
#define _XIE2YUE_GRAPH_H

/*

这个头文件的排布和代码都有些问题，需要重构。
The header file organization and code structure have some issues that need refactoring.


*/

#include <vector>
#include <random>
#include <iostream>


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

	void splitVal(Node *p,uint rp,Node *&l, Node *&r) {
	    l = r = nullptr;
	    Node *lt = nullptr, *rt = nullptr, *pt = nullptr;
	    uint pos = 0;
	    
	    while (p) {
	        uint left_size = p->ls ? p->ls->siz : 0;
	        uint mid = pos + left_size;
	        
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


	Node* merge(Node *l, Node *r) {
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
	void print(Node*p){
		if(!p)return;
		print(p->ls);
		std::cout<<p->data<<"\n";
		print(p->rs);
	}
	void print(){print(root);}
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
};


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
		
	uint addVertex() {
		V.emplace_back(idx);
		return idx++;
	}
	void addEdge(uint u, uint v, ll weight = 0) {
		if(u == v || u >= V.size() || v >= V.size()) return;
		V[u].addEdge(v, weight);
		++E;
	}
	void clear() {
		V.clear();
		idx = 0;
		E = 0;
	}
	void createRandomConnectedGraph0(uint n, uint m) {
		// 动态序号略隙采样(Dynamic Ordinal Gap-Skipping Sampling) + vector
		// 插入(insert) O(m) 查询(query) O(log m)
		// 蠢(stupid)
		if(n <= 1) return;
		if(m > n * (n - 1)) m = n * (n - 1);
		if(m < n - 1) m = n - 1 ;
		std::vector<uint>edgeIndex;
		static std::random_device rd;
		static std::mt19937 gen(rd());
		
		for(uint i = 0; i < n; ++i) {
			addVertex();
		}
		for(uint i = 1; i < n; ++i) {
			std::uniform_int_distribution<> dis(0, i - 1);
			edgeIndex.push_back(dis(gen) + i * (n - 1));
		}
		for(uint i = n; i <= m; ++i) {
			std::uniform_int_distribution<> dis(0 , n * (n - 1) - i);
			uint rp = dis(gen);
			uint l = 0, r = i;
			while(l < r) {
				uint mid = l + r >> 1;
				if(edgeIndex[mid] - mid <= rp) {
					l= mid + 1;
				}
				else r = mid;
			}
			edgeIndex.insert(edgeIndex.begin() + l, rp + l);
		}
		for(auto ei : edgeIndex) {
			auto v = ei / (n - 1);
			auto u = ei % (n - 1);
			u += u >= v;
			addEdge(u, v);
		}
	}
	
	void createRandomConnectedGraph1(uint n, uint m) {
		// 动态序号略隙采样(Dynamic Ordinal Gap-Skipping Sampling) + Treap
		// 插入(insert) O(log m) 查询(query) O(log m)
		// 这个代码真是何意味(I hate your work!)
		if(n <= 1) return;
		if(m > n * (n - 1)) m = n * (n - 1);
		if(m < n - 1) m = n - 1 ;
		Treap edgeIndex;
		Node *l, *r;
		static std::random_device rd;
		static std::mt19937 gen(rd());
		
		for(uint i = 0; i < n; ++i) {
			addVertex();
		}
		for(uint i = 1; i < n; ++i) {
			std::uniform_int_distribution<> dis(0, i - 1);
			auto val = dis(gen) + i * (n - 1);
			edgeIndex.splitVal(edgeIndex.root, val, l, r);
			edgeIndex.root=edgeIndex.merge(edgeIndex.merge(l, edgeIndex.newNode(val)), r);
		}
		for(uint i = n; i <= m; ++i) {
			std::uniform_int_distribution<> dis(0 , n * (n - 1) - i);
			uint rp = dis(gen);
			edgeIndex.split(edgeIndex.root, rp, l, r);
			edgeIndex.root=edgeIndex.merge(edgeIndex.merge(l, edgeIndex.newNode(rp + (l ? l->siz : 0 ))), r);
		}
		auto clr = [n, this](Node *p,auto self) -> void {
			if(p == nullptr) return;
			self(p->ls, self);
			self(p->rs, self);
			auto v = p->data / (n - 1);
			auto u = p->data % (n - 1);
			u += u >= v;
			addEdge(u, v);
			delete p;
		};
		Node* toClr = edgeIndex.root;
		edgeIndex.root=nullptr;
		clr(toClr, clr);
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