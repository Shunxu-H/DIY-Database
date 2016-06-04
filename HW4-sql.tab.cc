// A Bison parser, made by GNU Bison 3.0.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2013 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

//#include "lex.yy.cc"

#line 37 "HW4-sql.tab.cc" // lalr1.cc:399

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif



# include <vector>
# include <iostream>
# include <stdexcept>
# include <string>


#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif


namespace yy {
#line 115 "HW4-sql.tab.cc" // lalr1.cc:403

  template <class T, class S = std::vector<T> >
  class stack
  {
  public:
    // Hide our reversed order.
    typedef typename S::reverse_iterator iterator;
    typedef typename S::const_reverse_iterator const_iterator;

    stack ()
      : seq_ ()
    {
    }

    stack (unsigned int n)
      : seq_ (n)
    {
    }

    inline
    T&
    operator[] (unsigned int i)
    {
      return seq_[seq_.size () - 1 - i];
    }

    inline
    const T&
    operator[] (unsigned int i) const
    {
      return seq_[seq_.size () - 1 - i];
    }

    /// Steal the contents of \a t.
    ///
    /// Close to move-semantics.
    inline
    void
    push (T& t)
    {
      seq_.push_back (T());
      operator[](0).move (t);
    }

    inline
    void
    pop (unsigned int n = 1)
    {
      for (; n; --n)
        seq_.pop_back ();
    }

    void
    clear ()
    {
      seq_.clear ();
    }

    inline
    typename S::size_type
    size () const
    {
      return seq_.size ();
    }

    inline
    const_iterator
    begin () const
    {
      return seq_.rbegin ();
    }

    inline
    const_iterator
    end () const
    {
      return seq_.rend ();
    }

  private:
    stack (const stack&);
    stack& operator= (const stack&);
    /// The wrapped container.
    S seq_;
  };

  /// Present a slice of the top of a stack.
  template <class T, class S = stack<T> >
  class slice
  {
  public:
    slice (const S& stack, unsigned int range)
      : stack_ (stack)
      , range_ (range)
    {
    }

    inline
    const T&
    operator [] (unsigned int i) const
    {
      return stack_[range_ - i];
    }

  private:
    const S& stack_;
    unsigned int range_;
  };





  /// A Bison parser.
  class parser
  {
  public:
#ifndef YYSTYPE
    /// Symbol semantic values.
    typedef int semantic_type;
#else
    typedef YYSTYPE semantic_type;
#endif

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const std::string& m);
    };

    /// Tokens.
    struct token
    {
      enum yytokentype
      {
        IDENT = 258,
        NUMBER = 259,
        STRING = 260,
        NUL = 261,
        SELECT = 262,
        AS = 263,
        FROM = 264,
        WHERE = 265,
        GROUP = 266,
        BY = 267,
        HAVING = 268,
        ORDER = 269,
        ASC = 270,
        DESC = 271,
        INSERT = 272,
        INTO = 273,
        VALUES = 274,
        UPDATE = 275,
        SET = 276,
        DELETE = 277,
        CREATE = 278,
        TABLE = 279,
        DESCRIBE = 280,
        SHOW = 281,
        TABLES = 282,
        DROP = 283,
        PRIMARY = 284,
        KEY = 285,
        NOTEQ = 286,
        GEQ = 287,
        LEQ = 288,
        AND = 289,
        OR = 290,
        QUIT = 291
      };
    };

    /// (External) token type, as returned by yylex.
    typedef token::yytokentype token_type;

    /// Internal symbol number.
    typedef int symbol_number_type;

    /// Internal symbol number for tokens (subsumed by symbol_number_type).
    typedef unsigned char token_number_type;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol type
    /// via type_get().
    ///
    /// Provide access to semantic value.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ();

      /// Copy constructor.
      basic_symbol (const basic_symbol& other);

      /// Constructor for valueless symbols.
      basic_symbol (typename Base::kind_type t);

      /// Constructor for symbols with semantic value.
      basic_symbol (typename Base::kind_type t,
                    const semantic_type& v);

      ~basic_symbol ();

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

    private:
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& other);
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

      /// Copy constructor.
      by_type (const by_type& other);

      /// The symbol type as needed by the constructor.
      typedef token_type kind_type;

      /// Constructor from (external) token numbers.
      by_type (kind_type t);

      /// Steal the symbol type from \a that.
      void move (by_type& that);

      /// The (internal) type number (corresponding to \a type).
      /// -1 when this symbol is empty.
      symbol_number_type type_get () const;

      /// The token.
      token_type token () const;

      enum { empty = 0 };

      /// The symbol type.
      /// -1 when this symbol is empty.
      token_number_type type;
    };

    /// "External" symbols: returned by the scanner.
    typedef basic_symbol<by_type> symbol_type;


    /// Build a parser object.
    parser ();
    virtual ~parser ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param msg    a description of the syntax error.
    virtual void error (const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

  private:
    /// This class is not copyable.
    parser (const parser&);
    parser& operator= (const parser&);

    /// State numbers.
    typedef int state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yytoken   the lookahead token type, or yyempty_.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         symbol_number_type yytoken) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    static token_number_type yytranslate_ (int t);

    // Tables.
  // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
  // STATE-NUM.
  static const short int yypact_[];

  // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
  // Performed when YYTABLE does not specify something else to do.  Zero
  // means the default is an error.
  static const unsigned char yydefact_[];

  // YYPGOTO[NTERM-NUM].
  static const signed char yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const short int yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const short int yytable_[];

  static const short int yycheck_[];

  // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
  // symbol of state STATE-NUM.
  static const unsigned char yystos_[];

  // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
  static const unsigned char yyr1_[];

  // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
  static const unsigned char yyr2_[];


#if YYDEBUG
    /// For a symbol, its name in clear.
    static const char* const yytname_[];

  // YYRLINE[YYN] -- Source line where rule number YYN was defined.
  static const unsigned char yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    // Debugging.
    int yydebug_;
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state ();

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s);

      /// Copy constructor.
      by_state (const by_state& other);

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// "empty" when empty.
      symbol_number_type type_get () const;

      enum { empty = 0 };

      /// The state.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, symbol_type& sym);
      /// Assignment, needed by push_back.
      stack_symbol_type& operator= (const stack_symbol_type& that);
    };

    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, stack_symbol_type& s);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, state_type s, symbol_type& sym);

    /// Pop \a n symbols the three stacks.
    void yypop_ (unsigned int n = 1);

    // Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 224,     ///< Last index in yytable_.
      yynnts_ = 25,  ///< Number of nonterminal symbols.
      yyempty_ = -2,
      yyfinal_ = 2, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 48  ///< Number of tokens.
    };


  };



} // yy
#line 581 "HW4-sql.tab.cc" // lalr1.cc:403





// User implementation prologue.

#line 589 "HW4-sql.tab.cc" // lalr1.cc:407


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif



// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyempty = true)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 656 "HW4-sql.tab.cc" // lalr1.cc:474

  /// Build a parser object.
  parser::parser ()
#if YYDEBUG
     :yydebug_ (false),
      yycdebug_ (&std::cerr)
#endif
  {}

  parser::~parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  parser::syntax_error::syntax_error (const std::string& m)
    : std::runtime_error (m)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
  {
    value = other.value;
  }


  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v)
    : Base (t)
    , value (v)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t)
    : Base (t)
    , value ()
  {}

  template <typename Base>
  inline
  parser::basic_symbol<Base>::~basic_symbol ()
  {
  }

  template <typename Base>
  inline
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
  }

  // by_type.
  inline
  parser::by_type::by_type ()
     : type (empty)
  {}

  inline
  parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.type = empty;
  }

  inline
  int
  parser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  parser::by_state::by_state ()
    : state (empty)
  {}

  inline
  parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.state = empty;
  }

  inline
  parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  parser::symbol_number_type
  parser::by_state::type_get () const
  {
    return state == empty ? 0 : yystos_[state];
  }

  inline
  parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s)
  {
    value = that.value;
    // that is emptied.
    that.type = empty;
  }

  inline
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    return *this;
  }


  template <typename Base>
  inline
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.type_get ());
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " (";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::parse ()
  {
    /// Whether yyla contains a lookahead.
    bool yyempty = true;

    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyempty)
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
        yyempty = false;
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Discard the token being shifted.
    yyempty = true;

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;


      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 4:
#line 42 "HW4-sql.y" // lalr1.cc:847
    { return 0; }
#line 1050 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 5:
#line 46 "HW4-sql.y" // lalr1.cc:847
    { evalexpr(optimize(compile(makeexpr(OP_INSERTROW, 2, (yystack_[5].value), (yystack_[2].value))))); (yylhs.value)=0; }
#line 1056 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 6:
#line 49 "HW4-sql.y" // lalr1.cc:847
    { printf("Multi-row insert not implemented yet\n"); }
#line 1062 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 7:
#line 52 "HW4-sql.y" // lalr1.cc:847
    { print_relation(evalexpr(optimize(compile((yystack_[1].value))))); }
#line 1068 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 8:
#line 55 "HW4-sql.y" // lalr1.cc:847
    { printf("UPDATE not implemented yet\n"); }
#line 1074 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 9:
#line 58 "HW4-sql.y" // lalr1.cc:847
    { printf("DELETE not implemented yet\n"); }
#line 1080 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 10:
#line 61 "HW4-sql.y" // lalr1.cc:847
    { evalexpr(optimize(compile(makeexpr(OP_CREATETABLE, 2, (yystack_[4].value), (yystack_[2].value))))); (yylhs.value)=0; }
#line 1086 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 11:
#line 64 "HW4-sql.y" // lalr1.cc:847
    { printf("DESCRIBE not implemented yet\n"); }
#line 1092 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 12:
#line 68 "HW4-sql.y" // lalr1.cc:847
    { printf("SHOW TABLES not implemented yet\n"); }
#line 1098 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 13:
#line 72 "HW4-sql.y" // lalr1.cc:847
    { printf("DROP TABLE not implemented yet\n"); }
#line 1104 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 15:
#line 79 "HW4-sql.y" // lalr1.cc:847
    {
		  (yylhs.value) = makeexpr(OP_TABLENAME, 1, (yystack_[0].value), 0);
		}
#line 1112 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 16:
#line 85 "HW4-sql.y" // lalr1.cc:847
    {
		  (yylhs.value) = makeexpr(OP_COLNAME, 1, (yystack_[0].value), 0);
		}
#line 1120 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 18:
#line 92 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr((yystack_[1].value), 2, (yystack_[2].value), (yystack_[0].value)); }
#line 1126 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 19:
#line 94 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr((yystack_[3].value), 2, (yystack_[4].value), (yystack_[1].value)); }
#line 1132 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 20:
#line 96 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr((yystack_[3].value), 2, (yystack_[4].value), (yystack_[1].value)); }
#line 1138 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 21:
#line 98 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = (yystack_[1].value); }
#line 1144 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 22:
#line 100 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = (yystack_[1].value); }
#line 1150 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 23:
#line 102 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = (yystack_[0].value); }
#line 1156 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 24:
#line 106 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr(OP_FCALL, 2, makeexpr(OP_FNAME, 1, (yystack_[3].value), 0), (yystack_[1].value)); }
#line 1162 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 25:
#line 108 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr(OP_FCALL, 2, makeexpr(OP_FNAME, 1, (yystack_[2].value), 0), 0); }
#line 1168 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 26:
#line 112 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr(OP_RLIST, 2, (yystack_[0].value), 0); }
#line 1174 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 27:
#line 114 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr(OP_RLIST, 2, (yystack_[0].value), (yystack_[2].value)); }
#line 1180 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 28:
#line 119 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr(OP_COLNAME, 1, (yystack_[0].value), 0); }
#line 1186 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 29:
#line 121 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr(OP_NUMBER, 1, (yystack_[0].value), 0); }
#line 1192 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 30:
#line 123 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr(OP_STRING, 1, (yystack_[0].value), 0); }
#line 1198 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 31:
#line 127 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = (yystack_[4].value);
		  if((yystack_[3].value)) (yylhs.value) = makeexpr(OP_SELECTION, 2, (yylhs.value), (yystack_[3].value));
		  if((yystack_[2].value)) (yylhs.value) = makeexpr(OP_GROUP, 2, (yylhs.value), (yystack_[2].value));
		  (yylhs.value) = makeexpr(OP_PROJECTION, 2, (yylhs.value), (yystack_[6].value));
		  if((yystack_[1].value)) (yylhs.value) = makeexpr(OP_SELECTION, 2, (yylhs.value), (yystack_[1].value));
		  if((yystack_[0].value)) (yylhs.value) = makeexpr(OP_SORT, 2, (yylhs.value), (yystack_[0].value));
		}
#line 1210 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 32:
#line 136 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = 0; }
#line 1216 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 33:
#line 137 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = (yystack_[0].value); }
#line 1222 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 34:
#line 140 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = 0; }
#line 1228 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 35:
#line 141 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = (yystack_[0].value); }
#line 1234 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 36:
#line 144 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = 0; }
#line 1240 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 37:
#line 146 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = (yystack_[0].value); }
#line 1246 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 38:
#line 150 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr(OP_RLIST, 2, (yystack_[0].value), 0); }
#line 1252 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 39:
#line 152 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr(OP_RLIST, 2, (yystack_[0].value), (yystack_[2].value)); }
#line 1258 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 41:
#line 158 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = 0; }
#line 1264 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 42:
#line 160 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = (yystack_[0].value); }
#line 1270 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 43:
#line 164 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr(OP_RLIST, 2, (yystack_[0].value), 0); }
#line 1276 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 44:
#line 166 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr(OP_RLIST, 2, (yystack_[0].value), (yystack_[2].value)); }
#line 1282 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 45:
#line 170 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr(OP_SORTSPEC, 2, makeexpr(OP_NUMBER, 1, (yystack_[0].value), 0), 0); }
#line 1288 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 46:
#line 172 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr(OP_SORTSPEC, 2, makeexpr(OP_NUMBER, 1, (yystack_[1].value), 0), 0); }
#line 1294 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 47:
#line 174 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr(OP_SORTSPEC, 2, makeexpr(OP_NUMBER, 1, (yystack_[1].value), 0), makeexpr(OP_NULL, 0, 0, 0)); }
#line 1300 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 48:
#line 176 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr(OP_SORTSPEC, 2, makeexpr(OP_COLNAME, 1, (yystack_[0].value), 0), 0); }
#line 1306 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 49:
#line 178 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr(OP_SORTSPEC, 2, makeexpr(OP_COLNAME, 1, (yystack_[1].value), 0), 0); }
#line 1312 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 50:
#line 180 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr(OP_SORTSPEC, 2, makeexpr(OP_COLNAME, 1, (yystack_[1].value), 0), makeexpr(OP_NULL, 0, 0, 0)); }
#line 1318 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 51:
#line 184 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr(OP_RLIST, 2, (yystack_[0].value), 0); }
#line 1324 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 52:
#line 186 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr(OP_RLIST, 2, (yystack_[0].value), (yystack_[2].value)); }
#line 1330 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 53:
#line 190 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr(OP_OUTCOLNAME, 2, (yystack_[2].value), (yystack_[0].value)); }
#line 1336 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 54:
#line 192 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr(OP_OUTCOLNAME, 2, (yystack_[0].value), (yystack_[0].value)); }
#line 1342 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 55:
#line 196 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = (yystack_[0].value); }
#line 1348 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 56:
#line 198 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr(OP_PRODUCT, 2, (yystack_[2].value), (yystack_[0].value)); }
#line 1354 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 57:
#line 202 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr(OP_RLIST, 2, makeexpr(OP_NUMBER, 1, (yystack_[0].value), 0), 0); }
#line 1360 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 58:
#line 204 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr(OP_RLIST, 2, makeexpr(OP_STRING, 1, (yystack_[0].value), 0), 0); }
#line 1366 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 59:
#line 206 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr(OP_RLIST, 2, makeexpr(OP_NULL,0,0, 0), 0); }
#line 1372 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 60:
#line 208 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr(OP_RLIST, 2, makeexpr(OP_NUMBER, 1, (yystack_[0].value), 0), (yystack_[2].value)); }
#line 1378 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 61:
#line 210 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr(OP_RLIST, 2, makeexpr(OP_STRING, 1, (yystack_[0].value), 0), (yystack_[2].value)); }
#line 1384 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 62:
#line 212 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr(OP_RLIST, 2, makeexpr(OP_NULL, 0, 0, 0), (yystack_[2].value)); }
#line 1390 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 63:
#line 216 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr(OP_RLIST, 2, (yystack_[0].value), 0); }
#line 1396 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 64:
#line 218 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr(OP_RLIST, 2, (yystack_[0].value), (yystack_[2].value)); }
#line 1402 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 65:
#line 222 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr(OP_COLUMNDEF, 2, (yystack_[0].value), 0); }
#line 1408 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 66:
#line 224 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr(OP_COLUMNDEF, 2, (yystack_[1].value), makeexpr(OP_STRING, 1, (int)"KEY", 0)); }
#line 1414 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 67:
#line 226 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = makeexpr(OP_COLUMNDEF, 2, (yystack_[2].value), makeexpr(OP_STRING, 1, (int)"PRIMARY", 0)); }
#line 1420 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 68:
#line 229 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = OP_EQUAL; }
#line 1426 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 69:
#line 230 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = OP_NOTEQ; }
#line 1432 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 70:
#line 231 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = OP_GT; }
#line 1438 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 71:
#line 232 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = OP_LT; }
#line 1444 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 72:
#line 233 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = OP_GEQ; }
#line 1450 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 73:
#line 234 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = OP_LEQ; }
#line 1456 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 74:
#line 235 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = OP_PLUS; }
#line 1462 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 75:
#line 236 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = OP_BMINUS; }
#line 1468 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 76:
#line 237 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = OP_TIMES; }
#line 1474 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 77:
#line 238 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = OP_DIVIDE; }
#line 1480 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 78:
#line 239 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = OP_AND; }
#line 1486 "HW4-sql.tab.cc" // lalr1.cc:847
    break;

  case 79:
#line 240 "HW4-sql.y" // lalr1.cc:847
    { (yylhs.value) = OP_OR; }
#line 1492 "HW4-sql.tab.cc" // lalr1.cc:847
    break;


#line 1496 "HW4-sql.tab.cc" // lalr1.cc:847
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yysyntax_error_ (yystack_[0].state,
                                           yyempty ? yyempty_ : yyla.type_get ()));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyempty)
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyempty = true;
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }


      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyempty)
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyempty)
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type, symbol_number_type) const
  {
    return YY_("syntax error");
  }


  const signed char parser::yypact_ninf_ = -41;

  const signed char parser::yytable_ninf_ = -17;

  const short int
  parser::yypact_[] =
  {
     -41,     6,   -41,   -10,    11,     2,    27,    29,    21,    27,
      20,    40,    16,   -41,    34,   -41,    39,   -41,   -41,    32,
     -41,    75,   -41,   -41,    24,   -41,    27,   -41,    60,    27,
      27,    61,    62,    27,   -41,   -41,     5,    65,   109,    72,
      97,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,
     -41,   -41,   -41,    47,    27,    11,    56,    97,    94,    74,
     -41,   -41,    76,   -41,   177,   -36,   -41,   -41,   -41,   -41,
     -41,    32,   -41,   -41,    14,   -41,    78,    77,    88,    54,
      97,   -41,   -41,    54,   126,    90,    54,    27,   119,    82,
     -41,    54,   143,   -18,    37,   -41,   177,   -41,   -41,   177,
     -41,   121,   118,   -41,   -41,   -41,    43,    92,   -41,   115,
     -41,   110,    97,    97,    54,   132,   113,    85,    54,   -41,
     -41,   -41,   -41,   122,   -41,   177,   150,   -41,   -41,   -41,
     -41,   -41,   160,    97,    57,   -41,   -41,    52,    80,   123,
     -41,   -41,   -41,   -41,   -41,    57,   -41
  };

  const unsigned char
  parser::yydefact_[] =
  {
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     3,     0,    14,    28,    29,    30,     0,
      54,     0,    23,    17,     0,    51,     0,    15,     0,     0,
       0,     0,     0,     0,     4,     7,     0,    28,     0,     0,
       0,    69,    72,    73,    78,    79,    68,    70,    71,    74,
      75,    76,    77,     0,     0,     0,     0,     0,     0,     0,
      11,    12,     0,    25,    26,     0,    22,    21,    16,    53,
      28,     0,    18,    55,    32,    52,     0,     0,     0,     0,
       0,    13,    24,     0,     0,     0,     0,     0,    36,     0,
       6,     0,     0,    65,     0,    63,    27,    19,    20,    33,
      56,     0,    34,    57,    58,    59,     0,     0,     9,     0,
      66,     0,     0,     0,     0,    41,     0,     0,     0,    67,
      10,    64,    40,    37,    38,    35,     0,    31,     5,    60,
      61,    62,     0,     0,     0,     8,    39,    45,    48,    42,
      43,    46,    47,    49,    50,     0,    44
  };

  const signed char
  parser::yypgoto_[] =
  {
     -41,   -41,   -41,    -8,   -40,   -17,   -41,   -41,   114,   -15,
     -41,   -41,   -41,   -41,    46,   -41,   -41,    36,   -41,   127,
     -41,   -41,   -41,    84,   -41
  };

  const short int
  parser::yydefgoto_[] =
  {
      -1,     1,    13,    28,    20,    21,    22,    65,    23,    14,
      88,   115,   102,   123,   124,   127,   139,   140,    24,    25,
      74,   106,    94,    95,    53
  };

  const short int
  parser::yytable_[] =
  {
      69,    31,    38,    82,    39,    83,     2,     3,    37,    17,
      18,   109,   110,     4,    16,    17,    18,    78,    56,    64,
      26,    58,    59,     5,    86,    62,     6,    15,     7,     8,
      27,     9,    10,    54,    11,    37,    17,    18,    29,     4,
      93,    77,    12,    19,    63,    30,    73,    32,   -16,    19,
      70,    17,    18,    34,    84,    87,    85,    37,    17,    18,
      68,   137,    92,     4,    33,    55,    96,   141,   142,    99,
      19,    35,    93,   122,   107,    76,   111,    36,   112,   100,
     -16,    57,   116,    40,   117,    71,   103,   104,   105,   129,
     130,   131,    19,   122,   138,   143,   144,   125,    60,    61,
      68,   132,   118,    36,    79,   138,    41,    42,    43,    44,
      45,    67,    80,    81,    90,    46,    89,    47,    48,    49,
      50,    51,    52,    41,    42,    43,    44,    45,    91,    98,
     101,   114,    46,   113,    47,    48,    49,    50,    51,    52,
      41,    42,    43,    44,    45,   119,   126,   120,    66,    46,
     128,    47,    48,    49,    50,    51,    52,    41,    42,    43,
      44,    45,   134,   133,   145,    97,    46,    72,    47,    48,
      49,    50,    51,    52,    41,    42,    43,    44,    45,   136,
     108,   146,    75,    46,     0,    47,    48,    49,    50,    51,
      52,    41,    42,    43,    44,    45,   121,   135,     0,     0,
      46,     0,    47,    48,    49,    50,    51,    52,    41,    42,
      43,    44,    45,     0,     0,     0,     0,    46,     0,    47,
      48,    49,    50,    51,    52
  };

  const short int
  parser::yycheck_[] =
  {
      40,     9,    19,    39,    19,    41,     0,     1,     3,     4,
       5,    29,    30,     7,     3,     4,     5,    57,    26,    36,
      18,    29,    30,    17,    10,    33,    20,    37,    22,    23,
       3,    25,    26,     9,    28,     3,     4,     5,     9,     7,
      80,    56,    36,    38,    39,    24,    54,    27,     9,    38,
       3,     4,     5,    37,    71,    41,    71,     3,     4,     5,
       3,     4,    79,     7,    24,    41,    83,    15,    16,    86,
      38,    37,   112,   113,    91,    19,    39,    38,    41,    87,
      41,    21,    39,     8,    41,    38,     4,     5,     6,     4,
       5,     6,    38,   133,   134,    15,    16,   114,    37,    37,
       3,   118,    10,    38,    10,   145,    31,    32,    33,    34,
      35,    39,    38,    37,    37,    40,    38,    42,    43,    44,
      45,    46,    47,    31,    32,    33,    34,    35,    40,    39,
      11,    13,    40,    12,    42,    43,    44,    45,    46,    47,
      31,    32,    33,    34,    35,    30,    14,    37,    39,    40,
      37,    42,    43,    44,    45,    46,    47,    31,    32,    33,
      34,    35,    12,    41,    41,    39,    40,    53,    42,    43,
      44,    45,    46,    47,    31,    32,    33,    34,    35,   133,
      37,   145,    55,    40,    -1,    42,    43,    44,    45,    46,
      47,    31,    32,    33,    34,    35,   112,    37,    -1,    -1,
      40,    -1,    42,    43,    44,    45,    46,    47,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    -1,    42,
      43,    44,    45,    46,    47
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    49,     0,     1,     7,    17,    20,    22,    23,    25,
      26,    28,    36,    50,    57,    37,     3,     4,     5,    38,
      52,    53,    54,    56,    66,    67,    18,     3,    51,     9,
      24,    51,    27,    24,    37,    37,    38,     3,    53,    57,
       8,    31,    32,    33,    34,    35,    40,    42,    43,    44,
      45,    46,    47,    72,     9,    41,    51,    21,    51,    51,
      37,    37,    51,    39,    53,    55,    39,    39,     3,    52,
       3,    38,    56,    51,    68,    67,    19,    57,    52,    10,
      38,    37,    39,    41,    53,    57,    10,    41,    58,    38,
      37,    40,    53,    52,    70,    71,    53,    39,    39,    53,
      51,    11,    60,     4,     5,     6,    69,    53,    37,    29,
      30,    39,    41,    12,    13,    59,    39,    41,    10,    30,
      37,    71,    52,    61,    62,    53,    14,    63,    37,     4,
       5,     6,    53,    41,    12,    37,    62,     4,    52,    64,
      65,    15,    16,    15,    16,    41,    65
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    48,    49,    49,    49,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    51,    52,    53,    53,    53,
      53,    53,    53,    53,    54,    54,    55,    55,    56,    56,
      56,    57,    58,    58,    59,    59,    60,    60,    61,    61,
      62,    63,    63,    64,    64,    65,    65,    65,    65,    65,
      65,    66,    66,    67,    67,    68,    68,    69,    69,    69,
      69,    69,    69,    70,    70,    71,    71,    71,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72
  };

  const unsigned char
  parser::yyr2_[] =
  {
       0,     2,     0,     2,     3,     8,     5,     2,     9,     6,
       7,     3,     3,     4,     2,     1,     1,     1,     3,     5,
       5,     3,     3,     1,     4,     3,     1,     3,     1,     1,
       1,     8,     0,     2,     0,     2,     0,     3,     1,     3,
       1,     0,     3,     1,     3,     1,     2,     2,     1,     2,
       2,     1,     3,     3,     1,     1,     3,     1,     1,     1,
       3,     3,     3,     1,     3,     1,     2,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "$end", "error", "$undefined", "IDENT", "NUMBER", "STRING", "NUL",
  "SELECT", "AS", "FROM", "WHERE", "GROUP", "BY", "HAVING", "ORDER", "ASC",
  "DESC", "INSERT", "INTO", "VALUES", "UPDATE", "SET", "DELETE", "CREATE",
  "TABLE", "DESCRIBE", "SHOW", "TABLES", "DROP", "PRIMARY", "KEY", "NOTEQ",
  "GEQ", "LEQ", "AND", "OR", "QUIT", "';'", "'('", "')'", "'='", "','",
  "'>'", "'<'", "'+'", "'-'", "'*'", "'/'", "$accept", "program",
  "sql_command", "tablename", "colname", "expr", "fcall", "fncargs",
  "value", "select_expr", "whereclause", "havingclause", "groupclause",
  "grouplist", "groupspec", "orderclause", "orderlist", "orderspec",
  "projection", "outcol", "join", "data_list", "column_decls",
  "column_decl", "bin_op", YY_NULLPTR
  };


  const unsigned char
  parser::yyrline_[] =
  {
       0,    40,    40,    41,    42,    45,    48,    51,    54,    57,
      60,    63,    67,    71,    74,    78,    84,    90,    91,    93,
      95,    97,    99,   101,   105,   107,   111,   113,   118,   120,
     122,   126,   136,   137,   140,   141,   144,   145,   149,   151,
     155,   158,   159,   163,   165,   169,   171,   173,   175,   177,
     179,   183,   185,   189,   191,   195,   197,   201,   203,   205,
     207,   209,   211,   215,   217,   221,   223,   225,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
  parser::token_number_type
  parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      38,    39,    46,    44,    41,    45,     2,    47,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    37,
      43,    40,    42,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36
    };
    const unsigned int user_token_number_max_ = 291;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // yy
#line 1936 "HW4-sql.tab.cc" // lalr1.cc:1155
#line 243 "HW4-sql.y" // lalr1.cc:1156

yyerror(char *str)
{
	printf("Line %d: %s\n", linenum, str);
	return 1;
}


