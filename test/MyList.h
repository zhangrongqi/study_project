#pragma once

namespace MyList
{
	template <class _Ty>
	class ListIterator;

	template <class _Ty>
	class List;

	template <class _Ty>
	class ListNode
	{
		friend class List<_Ty>;
		friend class ListIterator<_Ty>;

	public:
		ListNode() : _Prev(nullptr), _Next(nullptr), _Value(_Ty()) {};

		ListNode(_Ty p_value, ListNode* p_perv = nullptr, ListNode* p_next = nullptr)
			: _Prev(p_perv), _Next(p_next), _Value(p_value) {
		};

		~ListNode() {};

	private:
		ListNode* _Prev;
		ListNode* _Next;

		_Ty _Value;
	};


	template <class _Ty>
	class ListIterator
	{
		typedef ListIterator<_Ty> _Lit;
	public:
		ListIterator() : _Ptr(nullptr) {};
		ListIterator(ListNode<_Ty>* p_ptr) : _Ptr(p_ptr) {};

		_Ty& operator*() { return _Ptr->_Value; };
		_Ty* operator->() { return &_Ptr->_Value; };

		_Lit& operator++() { _Ptr = _Ptr->_Next; return *this; };
		_Lit& operator--() { _Ptr = _Ptr->_Prev; return *this; };

		_Lit operator++(int) { _Lit _Tmp = *this; _Ptr = _Ptr->_Next; return _Tmp; };
		_Lit operator--(int) { _Lit _Tmp = *this; _Ptr = _Ptr->_Prev; return _Tmp; };

		bool operator==(const _Lit& _Right) const { return _Ptr == _Right._Ptr; };
		bool operator!=(const _Lit& _Right) const { return !(*this == _Right); };

	private:

		ListNode<_Ty>* _Ptr;
	};

	template<class _Ty>
	class List
	{
	public:

		typedef ListIterator<_Ty> iterator;
		typedef ListIterator<const _Ty> const_iterator;

		List() : _Head(nullptr), _Tail(nullptr), _Size(0) {};
		~List() {};

		iterator begin() { return iterator(_Head); };
		iterator end() { return iterator(_Tail->_Next); };

		const_iterator begin() const { return const_iterator(_Head); };
		const_iterator end() const { return const_iterator(_Tail->_Next); };

		void push_back(_Ty p_value) {
			ListNode<_Ty>* _NewNode = new ListNode<_Ty>(p_value, _Tail, nullptr);
			if (_Head == nullptr) {
				_Head = _NewNode;
			}
			else {
				_Tail->_Next = _NewNode;
			}
			_Tail = _NewNode;
			_Size++;
		};


		void push_front(_Ty p_value) {
			ListNode<_Ty>* _NewNode = new ListNode<_Ty>(p_value, nullptr, _Head);
			if (_Head == nullptr) {
				_Tail = _NewNode;
			}
			else {
				_Head->_Prev = _NewNode;
			}
			_Head = _NewNode;
			_Size++;
		};

		void pop_back() {
			if (_Head == nullptr) {
				return;
			}
			ListNode<_Ty>* _DelNode = _Tail;
			_Tail = _Tail->_Prev;
			if (_Tail != nullptr) {
				_Tail->_Next = nullptr;
			}
			delete _DelNode;
			_Size--;
		};

		void pop_front() {
			if (_Head == nullptr) {
				return;
			}
			ListNode<_Ty>* _DelNode = _Head;
			_Head = _Head->_Next;
			if (_Head != nullptr) {
				_Head->_Prev = nullptr;
			}
			delete _DelNode;
			_Size--;
		};

		_Ty& front() { return _Head->_Value; };
		_Ty& back() { return _Tail->_Value; };

		const _Ty& front() const { return _Head->_Value; };
		const _Ty& back() const { return _Tail->_Value; };

		void resize(int p_new_size, _Ty p_value = _Ty()) {
			if (p_new_size > _Size) {
				for (int i = _Size; i < p_new_size; i++) {
					push_back(p_value);
				}
			}
			else {
				for (int i = _Size; i > p_new_size; i--) {
					pop_back();
				}
			}
		};

		void swap(List<_Ty>& _Right) {
			std::swap(_Head, _Right._Head);
			std::swap(_Tail, _Right._Tail);
			std::swap(_Size, _Right._Size);
		};

		_Ty& operator[](int p_index) {
			ListNode<_Ty>* _CurNode = _Head;
			for (int i = 0; i < p_index; i++) {
				_CurNode = _CurNode->_Next;
			}
			return _CurNode->_Value;
		};

		_Ty& operator[](int p_index) const {
			ListNode<_Ty>* _CurNode = _Head;
			for (int i = 0; i < p_index; i++) {
				_CurNode = _CurNode->_Next;
			}
			return _CurNode->_Value;
		};

		int size() const { return _Size; };
		bool empty() const { return _Size == 0; };

		void clear() {
			while (_Head != nullptr) {
				ListNode<_Ty>* _DelNode = _Head;
				_Head = _Head->_Next;
				delete _DelNode;
			}
			_Tail = nullptr;
			_Size = 0;
		};

		void insert(iterator p_pos, _Ty p_value) {
			if (p_pos._Ptr == nullptr) {
				push_back(p_value);
				return;
			}
			if (p_pos._Ptr == _Head) {
				push_front(p_value);
				return;
			}
			ListNode<_Ty>* _NewNode = new ListNode<_Ty>(p_value, p_pos._Ptr->_Prev, p_pos._Ptr);
			p_pos._Ptr->_Prev->_Next = _NewNode;
			p_pos._Ptr->_Prev = _NewNode;
			_Size++;
		};

		void erase(iterator p_pos) {
			if (p_pos._Ptr == nullptr) {
				return;
			}
			if (p_pos._Ptr == _Head) {
				pop_front();
				return;
			}
			if (p_pos._Ptr == _Tail) {
				pop_back();
				return;
			}
			p_pos._Ptr->_Prev->_Next = p_pos._Ptr->_Next;
			p_pos._Ptr->_Next->_Prev = p_pos._Ptr->_Prev;
			delete p_pos._Ptr;
			_Size--;
		};

		void reverse() {
			ListNode<_Ty>* _CurNode = _Head;
			while (_CurNode != nullptr) {
				ListNode<_Ty>* _TempNode = _CurNode->_Next;
				_CurNode->_Next = _CurNode->_Prev;
				_CurNode->_Prev = _TempNode;
				_CurNode = _TempNode;
			}
			_TempNode = _Head;
			_Head = _Tail;
			_Tail = _TempNode;
		};

		void unique() {
			ListNode<_Ty>* _CurNode = _Head;
			while (_CurNode != nullptr) {
				ListNode<_Ty>* _NextNode = _CurNode->_Next;
				if (_NextNode != nullptr && _CurNode->_Value == _NextNode->_Value) {
					erase(iterator(_NextNode));
				}
				_CurNode = _NextNode;
			}
		};

		void sort() {
			ListNode<_Ty>* _CurNode = _Head;
			while (_CurNode != nullptr) {
				ListNode<_Ty>* _NextNode = _CurNode->_Next;
				while (_NextNode != nullptr) {
					if (_CurNode->_Value > _NextNode->_Value) {
						_Ty _TempValue = _CurNode->_Value;
						_CurNode->_Value = _NextNode->_Value;
						_NextNode->_Value = _TempValue;
					}
					_NextNode = _NextNode->_Next;
				}
				_CurNode = _CurNode->_Next;
			}
		};

		void merge(List<_Ty>& p_list) {
			ListNode<_Ty>* _CurNode = _Head;
			while (_CurNode != nullptr) {
				ListNode<_Ty>* _NextNode = _CurNode->_Next;
				while (_NextNode != nullptr) {
					if (_CurNode->_Value > _NextNode->_Value) {
						_Ty _TempValue = _CurNode->_Value;
						_CurNode->_Value = _NextNode->_Value;
						_NextNode->_Value = _TempValue;
					}
					_NextNode = _NextNode->_Next;
				}
				_CurNode = _CurNode->_Next;
			}
		};

	private:

		ListNode<_Ty>* _Head;
		ListNode<_Ty>* _Tail;
		int _Size;
	};

}

