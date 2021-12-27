// Generated from /home/parallels/code/db/dbtrain-mysql/src/parser/MYSQL.g4 by ANTLR 4.8
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class MYSQLParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.8", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		T__9=10, T__10=11, T__11=12, T__12=13, T__13=14, T__14=15, T__15=16, T__16=17, 
		T__17=18, T__18=19, T__19=20, T__20=21, T__21=22, T__22=23, T__23=24, 
		T__24=25, T__25=26, T__26=27, T__27=28, T__28=29, T__29=30, T__30=31, 
		T__31=32, T__32=33, T__33=34, T__34=35, T__35=36, T__36=37, T__37=38, 
		T__38=39, T__39=40, T__40=41, T__41=42, T__42=43, T__43=44, T__44=45, 
		T__45=46, T__46=47, T__47=48, T__48=49, T__49=50, T__50=51, T__51=52, 
		EqualOrAssign=53, Less=54, LessEqual=55, Greater=56, GreaterEqual=57, 
		NotEqual=58, Count=59, Average=60, Max=61, Min=62, Sum=63, Null=64, Identifier=65, 
		Integer=66, String=67, Float=68, Whitespace=69, Annotation=70;
	public static final int
		RULE_program = 0, RULE_statement = 1, RULE_db_statement = 2, RULE_io_statement = 3, 
		RULE_table_statement = 4, RULE_select_table = 5, RULE_alter_statement = 6, 
		RULE_field_list = 7, RULE_field = 8, RULE_type_ = 9, RULE_value_lists = 10, 
		RULE_value_list = 11, RULE_value = 12, RULE_where_and_clause = 13, RULE_where_clause = 14, 
		RULE_column = 15, RULE_expression = 16, RULE_set_clause = 17, RULE_selectors = 18, 
		RULE_selector = 19, RULE_identifiers = 20, RULE_operator_ = 21, RULE_aggregator = 22;
	private static String[] makeRuleNames() {
		return new String[] {
			"program", "statement", "db_statement", "io_statement", "table_statement", 
			"select_table", "alter_statement", "field_list", "field", "type_", "value_lists", 
			"value_list", "value", "where_and_clause", "where_clause", "column", 
			"expression", "set_clause", "selectors", "selector", "identifiers", "operator_", 
			"aggregator"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "';'", "'CREATE'", "'DATABASE'", "'DROP'", "'SHOW'", "'DATABASES'", 
			"'USE'", "'TABLES'", "'INDEXES'", "'LOAD'", "'FROM'", "'FILE'", "'TO'", 
			"'TABLE'", "'DUMP'", "'('", "')'", "'DESC'", "'INSERT'", "'INTO'", "'VALUES'", 
			"'DELETE'", "'WHERE'", "'UPDATE'", "'SET'", "'SELECT'", "'GROUP'", "'BY'", 
			"'LIMIT'", "'OFFSET'", "'ALTER'", "'ADD'", "'INDEX'", "'PRIMARY'", "'KEY'", 
			"'FOREIGN'", "'CONSTRAINT'", "'REFERENCES'", "'UNIQUE'", "'RENAME'", 
			"','", "'NOT'", "'DEFAULT'", "'INT'", "'VARCHAR'", "'FLOAT'", "'AND'", 
			"'IS'", "'IN'", "'LIKE'", "'.'", "'*'", "'='", "'<'", "'<='", "'>'", 
			"'>='", "'<>'", "'COUNT'", "'AVG'", "'MAX'", "'MIN'", "'SUM'", "'NULL'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, "EqualOrAssign", "Less", "LessEqual", "Greater", 
			"GreaterEqual", "NotEqual", "Count", "Average", "Max", "Min", "Sum", 
			"Null", "Identifier", "Integer", "String", "Float", "Whitespace", "Annotation"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "MYSQL.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public MYSQLParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	public static class ProgramContext extends ParserRuleContext {
		public TerminalNode EOF() { return getToken(MYSQLParser.EOF, 0); }
		public List<StatementContext> statement() {
			return getRuleContexts(StatementContext.class);
		}
		public StatementContext statement(int i) {
			return getRuleContext(StatementContext.class,i);
		}
		public ProgramContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_program; }
	}

	public final ProgramContext program() throws RecognitionException {
		ProgramContext _localctx = new ProgramContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_program);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(49);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__1) | (1L << T__3) | (1L << T__4) | (1L << T__6) | (1L << T__9) | (1L << T__14) | (1L << T__17) | (1L << T__18) | (1L << T__21) | (1L << T__23) | (1L << T__25) | (1L << T__30))) != 0) || _la==Null || _la==Annotation) {
				{
				{
				setState(46);
				statement();
				}
				}
				setState(51);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(52);
			match(EOF);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class StatementContext extends ParserRuleContext {
		public Db_statementContext db_statement() {
			return getRuleContext(Db_statementContext.class,0);
		}
		public Io_statementContext io_statement() {
			return getRuleContext(Io_statementContext.class,0);
		}
		public Table_statementContext table_statement() {
			return getRuleContext(Table_statementContext.class,0);
		}
		public Alter_statementContext alter_statement() {
			return getRuleContext(Alter_statementContext.class,0);
		}
		public TerminalNode Annotation() { return getToken(MYSQLParser.Annotation, 0); }
		public TerminalNode Null() { return getToken(MYSQLParser.Null, 0); }
		public StatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_statement; }
	}

	public final StatementContext statement() throws RecognitionException {
		StatementContext _localctx = new StatementContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_statement);
		try {
			setState(70);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,1,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(54);
				db_statement();
				setState(55);
				match(T__0);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(57);
				io_statement();
				setState(58);
				match(T__0);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(60);
				table_statement();
				setState(61);
				match(T__0);
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(63);
				alter_statement();
				setState(64);
				match(T__0);
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(66);
				match(Annotation);
				setState(67);
				match(T__0);
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(68);
				match(Null);
				setState(69);
				match(T__0);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Db_statementContext extends ParserRuleContext {
		public Db_statementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_db_statement; }
	 
		public Db_statementContext() { }
		public void copyFrom(Db_statementContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class Show_dbsContext extends Db_statementContext {
		public Show_dbsContext(Db_statementContext ctx) { copyFrom(ctx); }
	}
	public static class Drop_dbContext extends Db_statementContext {
		public TerminalNode Identifier() { return getToken(MYSQLParser.Identifier, 0); }
		public Drop_dbContext(Db_statementContext ctx) { copyFrom(ctx); }
	}
	public static class Show_tablesContext extends Db_statementContext {
		public Show_tablesContext(Db_statementContext ctx) { copyFrom(ctx); }
	}
	public static class Create_dbContext extends Db_statementContext {
		public TerminalNode Identifier() { return getToken(MYSQLParser.Identifier, 0); }
		public Create_dbContext(Db_statementContext ctx) { copyFrom(ctx); }
	}
	public static class Use_dbContext extends Db_statementContext {
		public TerminalNode Identifier() { return getToken(MYSQLParser.Identifier, 0); }
		public Use_dbContext(Db_statementContext ctx) { copyFrom(ctx); }
	}
	public static class Show_indexesContext extends Db_statementContext {
		public Show_indexesContext(Db_statementContext ctx) { copyFrom(ctx); }
	}

	public final Db_statementContext db_statement() throws RecognitionException {
		Db_statementContext _localctx = new Db_statementContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_db_statement);
		try {
			setState(86);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,2,_ctx) ) {
			case 1:
				_localctx = new Create_dbContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(72);
				match(T__1);
				setState(73);
				match(T__2);
				setState(74);
				match(Identifier);
				}
				break;
			case 2:
				_localctx = new Drop_dbContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(75);
				match(T__3);
				setState(76);
				match(T__2);
				setState(77);
				match(Identifier);
				}
				break;
			case 3:
				_localctx = new Show_dbsContext(_localctx);
				enterOuterAlt(_localctx, 3);
				{
				setState(78);
				match(T__4);
				setState(79);
				match(T__5);
				}
				break;
			case 4:
				_localctx = new Use_dbContext(_localctx);
				enterOuterAlt(_localctx, 4);
				{
				setState(80);
				match(T__6);
				setState(81);
				match(Identifier);
				}
				break;
			case 5:
				_localctx = new Show_tablesContext(_localctx);
				enterOuterAlt(_localctx, 5);
				{
				setState(82);
				match(T__4);
				setState(83);
				match(T__7);
				}
				break;
			case 6:
				_localctx = new Show_indexesContext(_localctx);
				enterOuterAlt(_localctx, 6);
				{
				setState(84);
				match(T__4);
				setState(85);
				match(T__8);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Io_statementContext extends ParserRuleContext {
		public Io_statementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_io_statement; }
	 
		public Io_statementContext() { }
		public void copyFrom(Io_statementContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class Dump_dataContext extends Io_statementContext {
		public TerminalNode String() { return getToken(MYSQLParser.String, 0); }
		public TerminalNode Identifier() { return getToken(MYSQLParser.Identifier, 0); }
		public Dump_dataContext(Io_statementContext ctx) { copyFrom(ctx); }
	}
	public static class Load_dataContext extends Io_statementContext {
		public TerminalNode String() { return getToken(MYSQLParser.String, 0); }
		public TerminalNode Identifier() { return getToken(MYSQLParser.Identifier, 0); }
		public Load_dataContext(Io_statementContext ctx) { copyFrom(ctx); }
	}

	public final Io_statementContext io_statement() throws RecognitionException {
		Io_statementContext _localctx = new Io_statementContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_io_statement);
		try {
			setState(102);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__9:
				_localctx = new Load_dataContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(88);
				match(T__9);
				setState(89);
				match(T__10);
				setState(90);
				match(T__11);
				setState(91);
				match(String);
				setState(92);
				match(T__12);
				setState(93);
				match(T__13);
				setState(94);
				match(Identifier);
				}
				break;
			case T__14:
				_localctx = new Dump_dataContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(95);
				match(T__14);
				setState(96);
				match(T__12);
				setState(97);
				match(T__11);
				setState(98);
				match(String);
				setState(99);
				match(T__10);
				setState(100);
				match(T__13);
				setState(101);
				match(Identifier);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Table_statementContext extends ParserRuleContext {
		public Table_statementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_table_statement; }
	 
		public Table_statementContext() { }
		public void copyFrom(Table_statementContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class Delete_from_tableContext extends Table_statementContext {
		public TerminalNode Identifier() { return getToken(MYSQLParser.Identifier, 0); }
		public Where_and_clauseContext where_and_clause() {
			return getRuleContext(Where_and_clauseContext.class,0);
		}
		public Delete_from_tableContext(Table_statementContext ctx) { copyFrom(ctx); }
	}
	public static class Insert_into_tableContext extends Table_statementContext {
		public TerminalNode Identifier() { return getToken(MYSQLParser.Identifier, 0); }
		public Value_listsContext value_lists() {
			return getRuleContext(Value_listsContext.class,0);
		}
		public Insert_into_tableContext(Table_statementContext ctx) { copyFrom(ctx); }
	}
	public static class Create_tableContext extends Table_statementContext {
		public TerminalNode Identifier() { return getToken(MYSQLParser.Identifier, 0); }
		public Field_listContext field_list() {
			return getRuleContext(Field_listContext.class,0);
		}
		public Create_tableContext(Table_statementContext ctx) { copyFrom(ctx); }
	}
	public static class Describe_tableContext extends Table_statementContext {
		public TerminalNode Identifier() { return getToken(MYSQLParser.Identifier, 0); }
		public Describe_tableContext(Table_statementContext ctx) { copyFrom(ctx); }
	}
	public static class Select_table_Context extends Table_statementContext {
		public Select_tableContext select_table() {
			return getRuleContext(Select_tableContext.class,0);
		}
		public Select_table_Context(Table_statementContext ctx) { copyFrom(ctx); }
	}
	public static class Drop_tableContext extends Table_statementContext {
		public TerminalNode Identifier() { return getToken(MYSQLParser.Identifier, 0); }
		public Drop_tableContext(Table_statementContext ctx) { copyFrom(ctx); }
	}
	public static class Update_tableContext extends Table_statementContext {
		public TerminalNode Identifier() { return getToken(MYSQLParser.Identifier, 0); }
		public Set_clauseContext set_clause() {
			return getRuleContext(Set_clauseContext.class,0);
		}
		public Where_and_clauseContext where_and_clause() {
			return getRuleContext(Where_and_clauseContext.class,0);
		}
		public Update_tableContext(Table_statementContext ctx) { copyFrom(ctx); }
	}

	public final Table_statementContext table_statement() throws RecognitionException {
		Table_statementContext _localctx = new Table_statementContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_table_statement);
		try {
			setState(134);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__1:
				_localctx = new Create_tableContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(104);
				match(T__1);
				setState(105);
				match(T__13);
				setState(106);
				match(Identifier);
				setState(107);
				match(T__15);
				setState(108);
				field_list();
				setState(109);
				match(T__16);
				}
				break;
			case T__3:
				_localctx = new Drop_tableContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(111);
				match(T__3);
				setState(112);
				match(T__13);
				setState(113);
				match(Identifier);
				}
				break;
			case T__17:
				_localctx = new Describe_tableContext(_localctx);
				enterOuterAlt(_localctx, 3);
				{
				setState(114);
				match(T__17);
				setState(115);
				match(Identifier);
				}
				break;
			case T__18:
				_localctx = new Insert_into_tableContext(_localctx);
				enterOuterAlt(_localctx, 4);
				{
				setState(116);
				match(T__18);
				setState(117);
				match(T__19);
				setState(118);
				match(Identifier);
				setState(119);
				match(T__20);
				setState(120);
				value_lists();
				}
				break;
			case T__21:
				_localctx = new Delete_from_tableContext(_localctx);
				enterOuterAlt(_localctx, 5);
				{
				setState(121);
				match(T__21);
				setState(122);
				match(T__10);
				setState(123);
				match(Identifier);
				setState(124);
				match(T__22);
				setState(125);
				where_and_clause();
				}
				break;
			case T__23:
				_localctx = new Update_tableContext(_localctx);
				enterOuterAlt(_localctx, 6);
				{
				setState(126);
				match(T__23);
				setState(127);
				match(Identifier);
				setState(128);
				match(T__24);
				setState(129);
				set_clause();
				setState(130);
				match(T__22);
				setState(131);
				where_and_clause();
				}
				break;
			case T__25:
				_localctx = new Select_table_Context(_localctx);
				enterOuterAlt(_localctx, 7);
				{
				setState(133);
				select_table();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Select_tableContext extends ParserRuleContext {
		public SelectorsContext selectors() {
			return getRuleContext(SelectorsContext.class,0);
		}
		public IdentifiersContext identifiers() {
			return getRuleContext(IdentifiersContext.class,0);
		}
		public Where_and_clauseContext where_and_clause() {
			return getRuleContext(Where_and_clauseContext.class,0);
		}
		public ColumnContext column() {
			return getRuleContext(ColumnContext.class,0);
		}
		public List<TerminalNode> Integer() { return getTokens(MYSQLParser.Integer); }
		public TerminalNode Integer(int i) {
			return getToken(MYSQLParser.Integer, i);
		}
		public Select_tableContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_select_table; }
	}

	public final Select_tableContext select_table() throws RecognitionException {
		Select_tableContext _localctx = new Select_tableContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_select_table);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(136);
			match(T__25);
			setState(137);
			selectors();
			setState(138);
			match(T__10);
			setState(139);
			identifiers();
			setState(142);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__22) {
				{
				setState(140);
				match(T__22);
				setState(141);
				where_and_clause();
				}
			}

			setState(147);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__26) {
				{
				setState(144);
				match(T__26);
				setState(145);
				match(T__27);
				setState(146);
				column();
				}
			}

			setState(155);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__28) {
				{
				setState(149);
				match(T__28);
				setState(150);
				match(Integer);
				setState(153);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__29) {
					{
					setState(151);
					match(T__29);
					setState(152);
					match(Integer);
					}
				}

				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Alter_statementContext extends ParserRuleContext {
		public Alter_statementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_alter_statement; }
	 
		public Alter_statementContext() { }
		public void copyFrom(Alter_statementContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class Alter_table_drop_pkContext extends Alter_statementContext {
		public TerminalNode Identifier() { return getToken(MYSQLParser.Identifier, 0); }
		public IdentifiersContext identifiers() {
			return getRuleContext(IdentifiersContext.class,0);
		}
		public Alter_table_drop_pkContext(Alter_statementContext ctx) { copyFrom(ctx); }
	}
	public static class Alter_table_add_foreign_keyContext extends Alter_statementContext {
		public List<TerminalNode> Identifier() { return getTokens(MYSQLParser.Identifier); }
		public TerminalNode Identifier(int i) {
			return getToken(MYSQLParser.Identifier, i);
		}
		public List<IdentifiersContext> identifiers() {
			return getRuleContexts(IdentifiersContext.class);
		}
		public IdentifiersContext identifiers(int i) {
			return getRuleContext(IdentifiersContext.class,i);
		}
		public Alter_table_add_foreign_keyContext(Alter_statementContext ctx) { copyFrom(ctx); }
	}
	public static class Alter_table_add_uniqueContext extends Alter_statementContext {
		public TerminalNode Identifier() { return getToken(MYSQLParser.Identifier, 0); }
		public IdentifiersContext identifiers() {
			return getRuleContext(IdentifiersContext.class,0);
		}
		public Alter_table_add_uniqueContext(Alter_statementContext ctx) { copyFrom(ctx); }
	}
	public static class Alter_drop_indexContext extends Alter_statementContext {
		public TerminalNode Identifier() { return getToken(MYSQLParser.Identifier, 0); }
		public IdentifiersContext identifiers() {
			return getRuleContext(IdentifiersContext.class,0);
		}
		public Alter_drop_indexContext(Alter_statementContext ctx) { copyFrom(ctx); }
	}
	public static class Alter_add_indexContext extends Alter_statementContext {
		public TerminalNode Identifier() { return getToken(MYSQLParser.Identifier, 0); }
		public IdentifiersContext identifiers() {
			return getRuleContext(IdentifiersContext.class,0);
		}
		public Alter_add_indexContext(Alter_statementContext ctx) { copyFrom(ctx); }
	}
	public static class Alter_table_renameContext extends Alter_statementContext {
		public List<TerminalNode> Identifier() { return getTokens(MYSQLParser.Identifier); }
		public TerminalNode Identifier(int i) {
			return getToken(MYSQLParser.Identifier, i);
		}
		public Alter_table_renameContext(Alter_statementContext ctx) { copyFrom(ctx); }
	}
	public static class Alter_table_drop_foreign_keyContext extends Alter_statementContext {
		public List<TerminalNode> Identifier() { return getTokens(MYSQLParser.Identifier); }
		public TerminalNode Identifier(int i) {
			return getToken(MYSQLParser.Identifier, i);
		}
		public Alter_table_drop_foreign_keyContext(Alter_statementContext ctx) { copyFrom(ctx); }
	}
	public static class Alter_table_add_pkContext extends Alter_statementContext {
		public List<TerminalNode> Identifier() { return getTokens(MYSQLParser.Identifier); }
		public TerminalNode Identifier(int i) {
			return getToken(MYSQLParser.Identifier, i);
		}
		public IdentifiersContext identifiers() {
			return getRuleContext(IdentifiersContext.class,0);
		}
		public Alter_table_add_pkContext(Alter_statementContext ctx) { copyFrom(ctx); }
	}

	public final Alter_statementContext alter_statement() throws RecognitionException {
		Alter_statementContext _localctx = new Alter_statementContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_alter_statement);
		int _la;
		try {
			setState(238);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,10,_ctx) ) {
			case 1:
				_localctx = new Alter_add_indexContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(157);
				match(T__30);
				setState(158);
				match(T__13);
				setState(159);
				match(Identifier);
				setState(160);
				match(T__31);
				setState(161);
				match(T__32);
				setState(162);
				match(T__15);
				setState(163);
				identifiers();
				setState(164);
				match(T__16);
				}
				break;
			case 2:
				_localctx = new Alter_drop_indexContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(166);
				match(T__30);
				setState(167);
				match(T__13);
				setState(168);
				match(Identifier);
				setState(169);
				match(T__3);
				setState(170);
				match(T__32);
				setState(171);
				match(T__15);
				setState(172);
				identifiers();
				setState(173);
				match(T__16);
				}
				break;
			case 3:
				_localctx = new Alter_table_drop_pkContext(_localctx);
				enterOuterAlt(_localctx, 3);
				{
				setState(175);
				match(T__30);
				setState(176);
				match(T__13);
				setState(177);
				match(Identifier);
				setState(178);
				match(T__3);
				setState(179);
				match(T__33);
				setState(180);
				match(T__34);
				setState(181);
				match(T__15);
				setState(182);
				identifiers();
				setState(183);
				match(T__16);
				}
				break;
			case 4:
				_localctx = new Alter_table_drop_foreign_keyContext(_localctx);
				enterOuterAlt(_localctx, 4);
				{
				setState(185);
				match(T__30);
				setState(186);
				match(T__13);
				setState(187);
				match(Identifier);
				setState(188);
				match(T__3);
				setState(189);
				match(T__35);
				setState(190);
				match(T__34);
				setState(191);
				match(Identifier);
				}
				break;
			case 5:
				_localctx = new Alter_table_add_pkContext(_localctx);
				enterOuterAlt(_localctx, 5);
				{
				setState(192);
				match(T__30);
				setState(193);
				match(T__13);
				setState(194);
				match(Identifier);
				setState(195);
				match(T__31);
				setState(198);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__36) {
					{
					setState(196);
					match(T__36);
					setState(197);
					match(Identifier);
					}
				}

				setState(200);
				match(T__33);
				setState(201);
				match(T__34);
				setState(202);
				match(T__15);
				setState(203);
				identifiers();
				setState(204);
				match(T__16);
				}
				break;
			case 6:
				_localctx = new Alter_table_add_foreign_keyContext(_localctx);
				enterOuterAlt(_localctx, 6);
				{
				setState(206);
				match(T__30);
				setState(207);
				match(T__13);
				setState(208);
				match(Identifier);
				setState(209);
				match(T__31);
				setState(210);
				match(T__36);
				setState(211);
				match(Identifier);
				setState(212);
				match(T__35);
				setState(213);
				match(T__34);
				setState(214);
				match(T__15);
				setState(215);
				identifiers();
				setState(216);
				match(T__16);
				setState(217);
				match(T__37);
				setState(218);
				match(Identifier);
				setState(219);
				match(T__15);
				setState(220);
				identifiers();
				setState(221);
				match(T__16);
				}
				break;
			case 7:
				_localctx = new Alter_table_add_uniqueContext(_localctx);
				enterOuterAlt(_localctx, 7);
				{
				setState(223);
				match(T__30);
				setState(224);
				match(T__13);
				setState(225);
				match(Identifier);
				setState(226);
				match(T__31);
				setState(227);
				match(T__38);
				setState(228);
				match(T__15);
				setState(229);
				identifiers();
				setState(230);
				match(T__16);
				}
				break;
			case 8:
				_localctx = new Alter_table_renameContext(_localctx);
				enterOuterAlt(_localctx, 8);
				{
				setState(232);
				match(T__30);
				setState(233);
				match(T__13);
				setState(234);
				match(Identifier);
				setState(235);
				match(T__39);
				setState(236);
				match(T__12);
				setState(237);
				match(Identifier);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Field_listContext extends ParserRuleContext {
		public List<FieldContext> field() {
			return getRuleContexts(FieldContext.class);
		}
		public FieldContext field(int i) {
			return getRuleContext(FieldContext.class,i);
		}
		public Field_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_field_list; }
	}

	public final Field_listContext field_list() throws RecognitionException {
		Field_listContext _localctx = new Field_listContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_field_list);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(240);
			field();
			setState(245);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__40) {
				{
				{
				setState(241);
				match(T__40);
				setState(242);
				field();
				}
				}
				setState(247);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class FieldContext extends ParserRuleContext {
		public FieldContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_field; }
	 
		public FieldContext() { }
		public void copyFrom(FieldContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class Primary_key_fieldContext extends FieldContext {
		public IdentifiersContext identifiers() {
			return getRuleContext(IdentifiersContext.class,0);
		}
		public TerminalNode Identifier() { return getToken(MYSQLParser.Identifier, 0); }
		public Primary_key_fieldContext(FieldContext ctx) { copyFrom(ctx); }
	}
	public static class Foreign_key_fieldContext extends FieldContext {
		public List<IdentifiersContext> identifiers() {
			return getRuleContexts(IdentifiersContext.class);
		}
		public IdentifiersContext identifiers(int i) {
			return getRuleContext(IdentifiersContext.class,i);
		}
		public List<TerminalNode> Identifier() { return getTokens(MYSQLParser.Identifier); }
		public TerminalNode Identifier(int i) {
			return getToken(MYSQLParser.Identifier, i);
		}
		public Foreign_key_fieldContext(FieldContext ctx) { copyFrom(ctx); }
	}
	public static class Normal_fieldContext extends FieldContext {
		public TerminalNode Identifier() { return getToken(MYSQLParser.Identifier, 0); }
		public Type_Context type_() {
			return getRuleContext(Type_Context.class,0);
		}
		public TerminalNode Null() { return getToken(MYSQLParser.Null, 0); }
		public ValueContext value() {
			return getRuleContext(ValueContext.class,0);
		}
		public Normal_fieldContext(FieldContext ctx) { copyFrom(ctx); }
	}

	public final FieldContext field() throws RecognitionException {
		FieldContext _localctx = new FieldContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_field);
		int _la;
		try {
			setState(281);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Identifier:
				_localctx = new Normal_fieldContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(248);
				match(Identifier);
				setState(249);
				type_();
				setState(252);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__41) {
					{
					setState(250);
					match(T__41);
					setState(251);
					match(Null);
					}
				}

				setState(256);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__42) {
					{
					setState(254);
					match(T__42);
					setState(255);
					value();
					}
				}

				}
				break;
			case T__33:
				_localctx = new Primary_key_fieldContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(258);
				match(T__33);
				setState(259);
				match(T__34);
				setState(261);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==Identifier) {
					{
					setState(260);
					match(Identifier);
					}
				}

				setState(263);
				match(T__15);
				setState(264);
				identifiers();
				setState(265);
				match(T__16);
				}
				break;
			case T__35:
				_localctx = new Foreign_key_fieldContext(_localctx);
				enterOuterAlt(_localctx, 3);
				{
				setState(267);
				match(T__35);
				setState(268);
				match(T__34);
				setState(270);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==Identifier) {
					{
					setState(269);
					match(Identifier);
					}
				}

				setState(272);
				match(T__15);
				setState(273);
				identifiers();
				setState(274);
				match(T__16);
				setState(275);
				match(T__37);
				setState(276);
				match(Identifier);
				setState(277);
				match(T__15);
				setState(278);
				identifiers();
				setState(279);
				match(T__16);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Type_Context extends ParserRuleContext {
		public TerminalNode Integer() { return getToken(MYSQLParser.Integer, 0); }
		public Type_Context(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_type_; }
	}

	public final Type_Context type_() throws RecognitionException {
		Type_Context _localctx = new Type_Context(_ctx, getState());
		enterRule(_localctx, 18, RULE_type_);
		try {
			setState(289);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__43:
				enterOuterAlt(_localctx, 1);
				{
				setState(283);
				match(T__43);
				}
				break;
			case T__44:
				enterOuterAlt(_localctx, 2);
				{
				setState(284);
				match(T__44);
				setState(285);
				match(T__15);
				setState(286);
				match(Integer);
				setState(287);
				match(T__16);
				}
				break;
			case T__45:
				enterOuterAlt(_localctx, 3);
				{
				setState(288);
				match(T__45);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Value_listsContext extends ParserRuleContext {
		public List<Value_listContext> value_list() {
			return getRuleContexts(Value_listContext.class);
		}
		public Value_listContext value_list(int i) {
			return getRuleContext(Value_listContext.class,i);
		}
		public Value_listsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_value_lists; }
	}

	public final Value_listsContext value_lists() throws RecognitionException {
		Value_listsContext _localctx = new Value_listsContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_value_lists);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(291);
			value_list();
			setState(296);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__40) {
				{
				{
				setState(292);
				match(T__40);
				setState(293);
				value_list();
				}
				}
				setState(298);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Value_listContext extends ParserRuleContext {
		public List<ValueContext> value() {
			return getRuleContexts(ValueContext.class);
		}
		public ValueContext value(int i) {
			return getRuleContext(ValueContext.class,i);
		}
		public Value_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_value_list; }
	}

	public final Value_listContext value_list() throws RecognitionException {
		Value_listContext _localctx = new Value_listContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_value_list);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(299);
			match(T__15);
			setState(300);
			value();
			setState(305);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__40) {
				{
				{
				setState(301);
				match(T__40);
				setState(302);
				value();
				}
				}
				setState(307);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(308);
			match(T__16);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ValueContext extends ParserRuleContext {
		public TerminalNode Integer() { return getToken(MYSQLParser.Integer, 0); }
		public TerminalNode String() { return getToken(MYSQLParser.String, 0); }
		public TerminalNode Float() { return getToken(MYSQLParser.Float, 0); }
		public TerminalNode Null() { return getToken(MYSQLParser.Null, 0); }
		public ValueContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_value; }
	}

	public final ValueContext value() throws RecognitionException {
		ValueContext _localctx = new ValueContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_value);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(310);
			_la = _input.LA(1);
			if ( !(((((_la - 64)) & ~0x3f) == 0 && ((1L << (_la - 64)) & ((1L << (Null - 64)) | (1L << (Integer - 64)) | (1L << (String - 64)) | (1L << (Float - 64)))) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Where_and_clauseContext extends ParserRuleContext {
		public List<Where_clauseContext> where_clause() {
			return getRuleContexts(Where_clauseContext.class);
		}
		public Where_clauseContext where_clause(int i) {
			return getRuleContext(Where_clauseContext.class,i);
		}
		public Where_and_clauseContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_where_and_clause; }
	}

	public final Where_and_clauseContext where_and_clause() throws RecognitionException {
		Where_and_clauseContext _localctx = new Where_and_clauseContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_where_and_clause);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(312);
			where_clause();
			setState(317);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__46) {
				{
				{
				setState(313);
				match(T__46);
				setState(314);
				where_clause();
				}
				}
				setState(319);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Where_clauseContext extends ParserRuleContext {
		public Where_clauseContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_where_clause; }
	 
		public Where_clauseContext() { }
		public void copyFrom(Where_clauseContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class Where_in_listContext extends Where_clauseContext {
		public ColumnContext column() {
			return getRuleContext(ColumnContext.class,0);
		}
		public Value_listContext value_list() {
			return getRuleContext(Value_listContext.class,0);
		}
		public Where_in_listContext(Where_clauseContext ctx) { copyFrom(ctx); }
	}
	public static class Where_operator_selectContext extends Where_clauseContext {
		public ColumnContext column() {
			return getRuleContext(ColumnContext.class,0);
		}
		public Operator_Context operator_() {
			return getRuleContext(Operator_Context.class,0);
		}
		public Select_tableContext select_table() {
			return getRuleContext(Select_tableContext.class,0);
		}
		public Where_operator_selectContext(Where_clauseContext ctx) { copyFrom(ctx); }
	}
	public static class Where_nullContext extends Where_clauseContext {
		public ColumnContext column() {
			return getRuleContext(ColumnContext.class,0);
		}
		public TerminalNode Null() { return getToken(MYSQLParser.Null, 0); }
		public Where_nullContext(Where_clauseContext ctx) { copyFrom(ctx); }
	}
	public static class Where_operator_expressionContext extends Where_clauseContext {
		public ColumnContext column() {
			return getRuleContext(ColumnContext.class,0);
		}
		public Operator_Context operator_() {
			return getRuleContext(Operator_Context.class,0);
		}
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public Where_operator_expressionContext(Where_clauseContext ctx) { copyFrom(ctx); }
	}
	public static class Where_in_selectContext extends Where_clauseContext {
		public ColumnContext column() {
			return getRuleContext(ColumnContext.class,0);
		}
		public Select_tableContext select_table() {
			return getRuleContext(Select_tableContext.class,0);
		}
		public Where_in_selectContext(Where_clauseContext ctx) { copyFrom(ctx); }
	}
	public static class Where_like_stringContext extends Where_clauseContext {
		public ColumnContext column() {
			return getRuleContext(ColumnContext.class,0);
		}
		public TerminalNode String() { return getToken(MYSQLParser.String, 0); }
		public Where_like_stringContext(Where_clauseContext ctx) { copyFrom(ctx); }
	}

	public final Where_clauseContext where_clause() throws RecognitionException {
		Where_clauseContext _localctx = new Where_clauseContext(_ctx, getState());
		enterRule(_localctx, 28, RULE_where_clause);
		int _la;
		try {
			setState(351);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,22,_ctx) ) {
			case 1:
				_localctx = new Where_operator_expressionContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(320);
				column();
				setState(321);
				operator_();
				setState(322);
				expression();
				}
				break;
			case 2:
				_localctx = new Where_operator_selectContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(324);
				column();
				setState(325);
				operator_();
				setState(326);
				match(T__15);
				setState(327);
				select_table();
				setState(328);
				match(T__16);
				}
				break;
			case 3:
				_localctx = new Where_nullContext(_localctx);
				enterOuterAlt(_localctx, 3);
				{
				setState(330);
				column();
				setState(331);
				match(T__47);
				setState(333);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__41) {
					{
					setState(332);
					match(T__41);
					}
				}

				setState(335);
				match(Null);
				}
				break;
			case 4:
				_localctx = new Where_in_listContext(_localctx);
				enterOuterAlt(_localctx, 4);
				{
				setState(337);
				column();
				setState(338);
				match(T__48);
				setState(339);
				value_list();
				}
				break;
			case 5:
				_localctx = new Where_in_selectContext(_localctx);
				enterOuterAlt(_localctx, 5);
				{
				setState(341);
				column();
				setState(342);
				match(T__48);
				setState(343);
				match(T__15);
				setState(344);
				select_table();
				setState(345);
				match(T__16);
				}
				break;
			case 6:
				_localctx = new Where_like_stringContext(_localctx);
				enterOuterAlt(_localctx, 6);
				{
				setState(347);
				column();
				setState(348);
				match(T__49);
				setState(349);
				match(String);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ColumnContext extends ParserRuleContext {
		public List<TerminalNode> Identifier() { return getTokens(MYSQLParser.Identifier); }
		public TerminalNode Identifier(int i) {
			return getToken(MYSQLParser.Identifier, i);
		}
		public ColumnContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_column; }
	}

	public final ColumnContext column() throws RecognitionException {
		ColumnContext _localctx = new ColumnContext(_ctx, getState());
		enterRule(_localctx, 30, RULE_column);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(353);
			match(Identifier);
			setState(354);
			match(T__50);
			setState(355);
			match(Identifier);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ExpressionContext extends ParserRuleContext {
		public ValueContext value() {
			return getRuleContext(ValueContext.class,0);
		}
		public ColumnContext column() {
			return getRuleContext(ColumnContext.class,0);
		}
		public ExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expression; }
	}

	public final ExpressionContext expression() throws RecognitionException {
		ExpressionContext _localctx = new ExpressionContext(_ctx, getState());
		enterRule(_localctx, 32, RULE_expression);
		try {
			setState(359);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Null:
			case Integer:
			case String:
			case Float:
				enterOuterAlt(_localctx, 1);
				{
				setState(357);
				value();
				}
				break;
			case Identifier:
				enterOuterAlt(_localctx, 2);
				{
				setState(358);
				column();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Set_clauseContext extends ParserRuleContext {
		public List<TerminalNode> Identifier() { return getTokens(MYSQLParser.Identifier); }
		public TerminalNode Identifier(int i) {
			return getToken(MYSQLParser.Identifier, i);
		}
		public List<TerminalNode> EqualOrAssign() { return getTokens(MYSQLParser.EqualOrAssign); }
		public TerminalNode EqualOrAssign(int i) {
			return getToken(MYSQLParser.EqualOrAssign, i);
		}
		public List<ValueContext> value() {
			return getRuleContexts(ValueContext.class);
		}
		public ValueContext value(int i) {
			return getRuleContext(ValueContext.class,i);
		}
		public Set_clauseContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_set_clause; }
	}

	public final Set_clauseContext set_clause() throws RecognitionException {
		Set_clauseContext _localctx = new Set_clauseContext(_ctx, getState());
		enterRule(_localctx, 34, RULE_set_clause);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(361);
			match(Identifier);
			setState(362);
			match(EqualOrAssign);
			setState(363);
			value();
			setState(370);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__40) {
				{
				{
				setState(364);
				match(T__40);
				setState(365);
				match(Identifier);
				setState(366);
				match(EqualOrAssign);
				setState(367);
				value();
				}
				}
				setState(372);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class SelectorsContext extends ParserRuleContext {
		public List<SelectorContext> selector() {
			return getRuleContexts(SelectorContext.class);
		}
		public SelectorContext selector(int i) {
			return getRuleContext(SelectorContext.class,i);
		}
		public SelectorsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_selectors; }
	}

	public final SelectorsContext selectors() throws RecognitionException {
		SelectorsContext _localctx = new SelectorsContext(_ctx, getState());
		enterRule(_localctx, 36, RULE_selectors);
		int _la;
		try {
			setState(382);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__51:
				enterOuterAlt(_localctx, 1);
				{
				setState(373);
				match(T__51);
				}
				break;
			case Count:
			case Average:
			case Max:
			case Min:
			case Sum:
			case Identifier:
				enterOuterAlt(_localctx, 2);
				{
				setState(374);
				selector();
				setState(379);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==T__40) {
					{
					{
					setState(375);
					match(T__40);
					setState(376);
					selector();
					}
					}
					setState(381);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class SelectorContext extends ParserRuleContext {
		public ColumnContext column() {
			return getRuleContext(ColumnContext.class,0);
		}
		public AggregatorContext aggregator() {
			return getRuleContext(AggregatorContext.class,0);
		}
		public TerminalNode Count() { return getToken(MYSQLParser.Count, 0); }
		public SelectorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_selector; }
	}

	public final SelectorContext selector() throws RecognitionException {
		SelectorContext _localctx = new SelectorContext(_ctx, getState());
		enterRule(_localctx, 38, RULE_selector);
		try {
			setState(394);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,27,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(384);
				column();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(385);
				aggregator();
				setState(386);
				match(T__15);
				setState(387);
				column();
				setState(388);
				match(T__16);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(390);
				match(Count);
				setState(391);
				match(T__15);
				setState(392);
				match(T__51);
				setState(393);
				match(T__16);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class IdentifiersContext extends ParserRuleContext {
		public List<TerminalNode> Identifier() { return getTokens(MYSQLParser.Identifier); }
		public TerminalNode Identifier(int i) {
			return getToken(MYSQLParser.Identifier, i);
		}
		public IdentifiersContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_identifiers; }
	}

	public final IdentifiersContext identifiers() throws RecognitionException {
		IdentifiersContext _localctx = new IdentifiersContext(_ctx, getState());
		enterRule(_localctx, 40, RULE_identifiers);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(396);
			match(Identifier);
			setState(401);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__40) {
				{
				{
				setState(397);
				match(T__40);
				setState(398);
				match(Identifier);
				}
				}
				setState(403);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Operator_Context extends ParserRuleContext {
		public TerminalNode EqualOrAssign() { return getToken(MYSQLParser.EqualOrAssign, 0); }
		public TerminalNode Less() { return getToken(MYSQLParser.Less, 0); }
		public TerminalNode LessEqual() { return getToken(MYSQLParser.LessEqual, 0); }
		public TerminalNode Greater() { return getToken(MYSQLParser.Greater, 0); }
		public TerminalNode GreaterEqual() { return getToken(MYSQLParser.GreaterEqual, 0); }
		public TerminalNode NotEqual() { return getToken(MYSQLParser.NotEqual, 0); }
		public Operator_Context(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_operator_; }
	}

	public final Operator_Context operator_() throws RecognitionException {
		Operator_Context _localctx = new Operator_Context(_ctx, getState());
		enterRule(_localctx, 42, RULE_operator_);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(404);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << EqualOrAssign) | (1L << Less) | (1L << LessEqual) | (1L << Greater) | (1L << GreaterEqual) | (1L << NotEqual))) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class AggregatorContext extends ParserRuleContext {
		public TerminalNode Count() { return getToken(MYSQLParser.Count, 0); }
		public TerminalNode Average() { return getToken(MYSQLParser.Average, 0); }
		public TerminalNode Max() { return getToken(MYSQLParser.Max, 0); }
		public TerminalNode Min() { return getToken(MYSQLParser.Min, 0); }
		public TerminalNode Sum() { return getToken(MYSQLParser.Sum, 0); }
		public AggregatorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_aggregator; }
	}

	public final AggregatorContext aggregator() throws RecognitionException {
		AggregatorContext _localctx = new AggregatorContext(_ctx, getState());
		enterRule(_localctx, 44, RULE_aggregator);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(406);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << Count) | (1L << Average) | (1L << Max) | (1L << Min) | (1L << Sum))) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\3H\u019b\4\2\t\2\4"+
		"\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13\t"+
		"\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22\t\22"+
		"\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\3\2\7\2\62"+
		"\n\2\f\2\16\2\65\13\2\3\2\3\2\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3"+
		"\3\3\3\3\3\3\3\3\3\3\3\3\5\3I\n\3\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4"+
		"\3\4\3\4\3\4\3\4\3\4\5\4Y\n\4\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\5"+
		"\3\5\3\5\3\5\3\5\5\5i\n\5\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6"+
		"\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3"+
		"\6\3\6\5\6\u0089\n\6\3\7\3\7\3\7\3\7\3\7\3\7\5\7\u0091\n\7\3\7\3\7\3\7"+
		"\5\7\u0096\n\7\3\7\3\7\3\7\3\7\5\7\u009c\n\7\5\7\u009e\n\7\3\b\3\b\3\b"+
		"\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3"+
		"\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b"+
		"\3\b\3\b\3\b\5\b\u00c9\n\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b"+
		"\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3"+
		"\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\5\b\u00f1\n\b\3\t\3\t\3\t\7\t\u00f6"+
		"\n\t\f\t\16\t\u00f9\13\t\3\n\3\n\3\n\3\n\5\n\u00ff\n\n\3\n\3\n\5\n\u0103"+
		"\n\n\3\n\3\n\3\n\5\n\u0108\n\n\3\n\3\n\3\n\3\n\3\n\3\n\3\n\5\n\u0111\n"+
		"\n\3\n\3\n\3\n\3\n\3\n\3\n\3\n\3\n\3\n\5\n\u011c\n\n\3\13\3\13\3\13\3"+
		"\13\3\13\3\13\5\13\u0124\n\13\3\f\3\f\3\f\7\f\u0129\n\f\f\f\16\f\u012c"+
		"\13\f\3\r\3\r\3\r\3\r\7\r\u0132\n\r\f\r\16\r\u0135\13\r\3\r\3\r\3\16\3"+
		"\16\3\17\3\17\3\17\7\17\u013e\n\17\f\17\16\17\u0141\13\17\3\20\3\20\3"+
		"\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\5\20\u0150\n\20"+
		"\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20"+
		"\3\20\3\20\5\20\u0162\n\20\3\21\3\21\3\21\3\21\3\22\3\22\5\22\u016a\n"+
		"\22\3\23\3\23\3\23\3\23\3\23\3\23\3\23\7\23\u0173\n\23\f\23\16\23\u0176"+
		"\13\23\3\24\3\24\3\24\3\24\7\24\u017c\n\24\f\24\16\24\u017f\13\24\5\24"+
		"\u0181\n\24\3\25\3\25\3\25\3\25\3\25\3\25\3\25\3\25\3\25\3\25\5\25\u018d"+
		"\n\25\3\26\3\26\3\26\7\26\u0192\n\26\f\26\16\26\u0195\13\26\3\27\3\27"+
		"\3\30\3\30\3\30\2\2\31\2\4\6\b\n\f\16\20\22\24\26\30\32\34\36 \"$&(*,"+
		".\2\5\4\2BBDF\3\2\67<\3\2=A\2\u01ba\2\63\3\2\2\2\4H\3\2\2\2\6X\3\2\2\2"+
		"\bh\3\2\2\2\n\u0088\3\2\2\2\f\u008a\3\2\2\2\16\u00f0\3\2\2\2\20\u00f2"+
		"\3\2\2\2\22\u011b\3\2\2\2\24\u0123\3\2\2\2\26\u0125\3\2\2\2\30\u012d\3"+
		"\2\2\2\32\u0138\3\2\2\2\34\u013a\3\2\2\2\36\u0161\3\2\2\2 \u0163\3\2\2"+
		"\2\"\u0169\3\2\2\2$\u016b\3\2\2\2&\u0180\3\2\2\2(\u018c\3\2\2\2*\u018e"+
		"\3\2\2\2,\u0196\3\2\2\2.\u0198\3\2\2\2\60\62\5\4\3\2\61\60\3\2\2\2\62"+
		"\65\3\2\2\2\63\61\3\2\2\2\63\64\3\2\2\2\64\66\3\2\2\2\65\63\3\2\2\2\66"+
		"\67\7\2\2\3\67\3\3\2\2\289\5\6\4\29:\7\3\2\2:I\3\2\2\2;<\5\b\5\2<=\7\3"+
		"\2\2=I\3\2\2\2>?\5\n\6\2?@\7\3\2\2@I\3\2\2\2AB\5\16\b\2BC\7\3\2\2CI\3"+
		"\2\2\2DE\7H\2\2EI\7\3\2\2FG\7B\2\2GI\7\3\2\2H8\3\2\2\2H;\3\2\2\2H>\3\2"+
		"\2\2HA\3\2\2\2HD\3\2\2\2HF\3\2\2\2I\5\3\2\2\2JK\7\4\2\2KL\7\5\2\2LY\7"+
		"C\2\2MN\7\6\2\2NO\7\5\2\2OY\7C\2\2PQ\7\7\2\2QY\7\b\2\2RS\7\t\2\2SY\7C"+
		"\2\2TU\7\7\2\2UY\7\n\2\2VW\7\7\2\2WY\7\13\2\2XJ\3\2\2\2XM\3\2\2\2XP\3"+
		"\2\2\2XR\3\2\2\2XT\3\2\2\2XV\3\2\2\2Y\7\3\2\2\2Z[\7\f\2\2[\\\7\r\2\2\\"+
		"]\7\16\2\2]^\7E\2\2^_\7\17\2\2_`\7\20\2\2`i\7C\2\2ab\7\21\2\2bc\7\17\2"+
		"\2cd\7\16\2\2de\7E\2\2ef\7\r\2\2fg\7\20\2\2gi\7C\2\2hZ\3\2\2\2ha\3\2\2"+
		"\2i\t\3\2\2\2jk\7\4\2\2kl\7\20\2\2lm\7C\2\2mn\7\22\2\2no\5\20\t\2op\7"+
		"\23\2\2p\u0089\3\2\2\2qr\7\6\2\2rs\7\20\2\2s\u0089\7C\2\2tu\7\24\2\2u"+
		"\u0089\7C\2\2vw\7\25\2\2wx\7\26\2\2xy\7C\2\2yz\7\27\2\2z\u0089\5\26\f"+
		"\2{|\7\30\2\2|}\7\r\2\2}~\7C\2\2~\177\7\31\2\2\177\u0089\5\34\17\2\u0080"+
		"\u0081\7\32\2\2\u0081\u0082\7C\2\2\u0082\u0083\7\33\2\2\u0083\u0084\5"+
		"$\23\2\u0084\u0085\7\31\2\2\u0085\u0086\5\34\17\2\u0086\u0089\3\2\2\2"+
		"\u0087\u0089\5\f\7\2\u0088j\3\2\2\2\u0088q\3\2\2\2\u0088t\3\2\2\2\u0088"+
		"v\3\2\2\2\u0088{\3\2\2\2\u0088\u0080\3\2\2\2\u0088\u0087\3\2\2\2\u0089"+
		"\13\3\2\2\2\u008a\u008b\7\34\2\2\u008b\u008c\5&\24\2\u008c\u008d\7\r\2"+
		"\2\u008d\u0090\5*\26\2\u008e\u008f\7\31\2\2\u008f\u0091\5\34\17\2\u0090"+
		"\u008e\3\2\2\2\u0090\u0091\3\2\2\2\u0091\u0095\3\2\2\2\u0092\u0093\7\35"+
		"\2\2\u0093\u0094\7\36\2\2\u0094\u0096\5 \21\2\u0095\u0092\3\2\2\2\u0095"+
		"\u0096\3\2\2\2\u0096\u009d\3\2\2\2\u0097\u0098\7\37\2\2\u0098\u009b\7"+
		"D\2\2\u0099\u009a\7 \2\2\u009a\u009c\7D\2\2\u009b\u0099\3\2\2\2\u009b"+
		"\u009c\3\2\2\2\u009c\u009e\3\2\2\2\u009d\u0097\3\2\2\2\u009d\u009e\3\2"+
		"\2\2\u009e\r\3\2\2\2\u009f\u00a0\7!\2\2\u00a0\u00a1\7\20\2\2\u00a1\u00a2"+
		"\7C\2\2\u00a2\u00a3\7\"\2\2\u00a3\u00a4\7#\2\2\u00a4\u00a5\7\22\2\2\u00a5"+
		"\u00a6\5*\26\2\u00a6\u00a7\7\23\2\2\u00a7\u00f1\3\2\2\2\u00a8\u00a9\7"+
		"!\2\2\u00a9\u00aa\7\20\2\2\u00aa\u00ab\7C\2\2\u00ab\u00ac\7\6\2\2\u00ac"+
		"\u00ad\7#\2\2\u00ad\u00ae\7\22\2\2\u00ae\u00af\5*\26\2\u00af\u00b0\7\23"+
		"\2\2\u00b0\u00f1\3\2\2\2\u00b1\u00b2\7!\2\2\u00b2\u00b3\7\20\2\2\u00b3"+
		"\u00b4\7C\2\2\u00b4\u00b5\7\6\2\2\u00b5\u00b6\7$\2\2\u00b6\u00b7\7%\2"+
		"\2\u00b7\u00b8\7\22\2\2\u00b8\u00b9\5*\26\2\u00b9\u00ba\7\23\2\2\u00ba"+
		"\u00f1\3\2\2\2\u00bb\u00bc\7!\2\2\u00bc\u00bd\7\20\2\2\u00bd\u00be\7C"+
		"\2\2\u00be\u00bf\7\6\2\2\u00bf\u00c0\7&\2\2\u00c0\u00c1\7%\2\2\u00c1\u00f1"+
		"\7C\2\2\u00c2\u00c3\7!\2\2\u00c3\u00c4\7\20\2\2\u00c4\u00c5\7C\2\2\u00c5"+
		"\u00c8\7\"\2\2\u00c6\u00c7\7\'\2\2\u00c7\u00c9\7C\2\2\u00c8\u00c6\3\2"+
		"\2\2\u00c8\u00c9\3\2\2\2\u00c9\u00ca\3\2\2\2\u00ca\u00cb\7$\2\2\u00cb"+
		"\u00cc\7%\2\2\u00cc\u00cd\7\22\2\2\u00cd\u00ce\5*\26\2\u00ce\u00cf\7\23"+
		"\2\2\u00cf\u00f1\3\2\2\2\u00d0\u00d1\7!\2\2\u00d1\u00d2\7\20\2\2\u00d2"+
		"\u00d3\7C\2\2\u00d3\u00d4\7\"\2\2\u00d4\u00d5\7\'\2\2\u00d5\u00d6\7C\2"+
		"\2\u00d6\u00d7\7&\2\2\u00d7\u00d8\7%\2\2\u00d8\u00d9\7\22\2\2\u00d9\u00da"+
		"\5*\26\2\u00da\u00db\7\23\2\2\u00db\u00dc\7(\2\2\u00dc\u00dd\7C\2\2\u00dd"+
		"\u00de\7\22\2\2\u00de\u00df\5*\26\2\u00df\u00e0\7\23\2\2\u00e0\u00f1\3"+
		"\2\2\2\u00e1\u00e2\7!\2\2\u00e2\u00e3\7\20\2\2\u00e3\u00e4\7C\2\2\u00e4"+
		"\u00e5\7\"\2\2\u00e5\u00e6\7)\2\2\u00e6\u00e7\7\22\2\2\u00e7\u00e8\5*"+
		"\26\2\u00e8\u00e9\7\23\2\2\u00e9\u00f1\3\2\2\2\u00ea\u00eb\7!\2\2\u00eb"+
		"\u00ec\7\20\2\2\u00ec\u00ed\7C\2\2\u00ed\u00ee\7*\2\2\u00ee\u00ef\7\17"+
		"\2\2\u00ef\u00f1\7C\2\2\u00f0\u009f\3\2\2\2\u00f0\u00a8\3\2\2\2\u00f0"+
		"\u00b1\3\2\2\2\u00f0\u00bb\3\2\2\2\u00f0\u00c2\3\2\2\2\u00f0\u00d0\3\2"+
		"\2\2\u00f0\u00e1\3\2\2\2\u00f0\u00ea\3\2\2\2\u00f1\17\3\2\2\2\u00f2\u00f7"+
		"\5\22\n\2\u00f3\u00f4\7+\2\2\u00f4\u00f6\5\22\n\2\u00f5\u00f3\3\2\2\2"+
		"\u00f6\u00f9\3\2\2\2\u00f7\u00f5\3\2\2\2\u00f7\u00f8\3\2\2\2\u00f8\21"+
		"\3\2\2\2\u00f9\u00f7\3\2\2\2\u00fa\u00fb\7C\2\2\u00fb\u00fe\5\24\13\2"+
		"\u00fc\u00fd\7,\2\2\u00fd\u00ff\7B\2\2\u00fe\u00fc\3\2\2\2\u00fe\u00ff"+
		"\3\2\2\2\u00ff\u0102\3\2\2\2\u0100\u0101\7-\2\2\u0101\u0103\5\32\16\2"+
		"\u0102\u0100\3\2\2\2\u0102\u0103\3\2\2\2\u0103\u011c\3\2\2\2\u0104\u0105"+
		"\7$\2\2\u0105\u0107\7%\2\2\u0106\u0108\7C\2\2\u0107\u0106\3\2\2\2\u0107"+
		"\u0108\3\2\2\2\u0108\u0109\3\2\2\2\u0109\u010a\7\22\2\2\u010a\u010b\5"+
		"*\26\2\u010b\u010c\7\23\2\2\u010c\u011c\3\2\2\2\u010d\u010e\7&\2\2\u010e"+
		"\u0110\7%\2\2\u010f\u0111\7C\2\2\u0110\u010f\3\2\2\2\u0110\u0111\3\2\2"+
		"\2\u0111\u0112\3\2\2\2\u0112\u0113\7\22\2\2\u0113\u0114\5*\26\2\u0114"+
		"\u0115\7\23\2\2\u0115\u0116\7(\2\2\u0116\u0117\7C\2\2\u0117\u0118\7\22"+
		"\2\2\u0118\u0119\5*\26\2\u0119\u011a\7\23\2\2\u011a\u011c\3\2\2\2\u011b"+
		"\u00fa\3\2\2\2\u011b\u0104\3\2\2\2\u011b\u010d\3\2\2\2\u011c\23\3\2\2"+
		"\2\u011d\u0124\7.\2\2\u011e\u011f\7/\2\2\u011f\u0120\7\22\2\2\u0120\u0121"+
		"\7D\2\2\u0121\u0124\7\23\2\2\u0122\u0124\7\60\2\2\u0123\u011d\3\2\2\2"+
		"\u0123\u011e\3\2\2\2\u0123\u0122\3\2\2\2\u0124\25\3\2\2\2\u0125\u012a"+
		"\5\30\r\2\u0126\u0127\7+\2\2\u0127\u0129\5\30\r\2\u0128\u0126\3\2\2\2"+
		"\u0129\u012c\3\2\2\2\u012a\u0128\3\2\2\2\u012a\u012b\3\2\2\2\u012b\27"+
		"\3\2\2\2\u012c\u012a\3\2\2\2\u012d\u012e\7\22\2\2\u012e\u0133\5\32\16"+
		"\2\u012f\u0130\7+\2\2\u0130\u0132\5\32\16\2\u0131\u012f\3\2\2\2\u0132"+
		"\u0135\3\2\2\2\u0133\u0131\3\2\2\2\u0133\u0134\3\2\2\2\u0134\u0136\3\2"+
		"\2\2\u0135\u0133\3\2\2\2\u0136\u0137\7\23\2\2\u0137\31\3\2\2\2\u0138\u0139"+
		"\t\2\2\2\u0139\33\3\2\2\2\u013a\u013f\5\36\20\2\u013b\u013c\7\61\2\2\u013c"+
		"\u013e\5\36\20\2\u013d\u013b\3\2\2\2\u013e\u0141\3\2\2\2\u013f\u013d\3"+
		"\2\2\2\u013f\u0140\3\2\2\2\u0140\35\3\2\2\2\u0141\u013f\3\2\2\2\u0142"+
		"\u0143\5 \21\2\u0143\u0144\5,\27\2\u0144\u0145\5\"\22\2\u0145\u0162\3"+
		"\2\2\2\u0146\u0147\5 \21\2\u0147\u0148\5,\27\2\u0148\u0149\7\22\2\2\u0149"+
		"\u014a\5\f\7\2\u014a\u014b\7\23\2\2\u014b\u0162\3\2\2\2\u014c\u014d\5"+
		" \21\2\u014d\u014f\7\62\2\2\u014e\u0150\7,\2\2\u014f\u014e\3\2\2\2\u014f"+
		"\u0150\3\2\2\2\u0150\u0151\3\2\2\2\u0151\u0152\7B\2\2\u0152\u0162\3\2"+
		"\2\2\u0153\u0154\5 \21\2\u0154\u0155\7\63\2\2\u0155\u0156\5\30\r\2\u0156"+
		"\u0162\3\2\2\2\u0157\u0158\5 \21\2\u0158\u0159\7\63\2\2\u0159\u015a\7"+
		"\22\2\2\u015a\u015b\5\f\7\2\u015b\u015c\7\23\2\2\u015c\u0162\3\2\2\2\u015d"+
		"\u015e\5 \21\2\u015e\u015f\7\64\2\2\u015f\u0160\7E\2\2\u0160\u0162\3\2"+
		"\2\2\u0161\u0142\3\2\2\2\u0161\u0146\3\2\2\2\u0161\u014c\3\2\2\2\u0161"+
		"\u0153\3\2\2\2\u0161\u0157\3\2\2\2\u0161\u015d\3\2\2\2\u0162\37\3\2\2"+
		"\2\u0163\u0164\7C\2\2\u0164\u0165\7\65\2\2\u0165\u0166\7C\2\2\u0166!\3"+
		"\2\2\2\u0167\u016a\5\32\16\2\u0168\u016a\5 \21\2\u0169\u0167\3\2\2\2\u0169"+
		"\u0168\3\2\2\2\u016a#\3\2\2\2\u016b\u016c\7C\2\2\u016c\u016d\7\67\2\2"+
		"\u016d\u0174\5\32\16\2\u016e\u016f\7+\2\2\u016f\u0170\7C\2\2\u0170\u0171"+
		"\7\67\2\2\u0171\u0173\5\32\16\2\u0172\u016e\3\2\2\2\u0173\u0176\3\2\2"+
		"\2\u0174\u0172\3\2\2\2\u0174\u0175\3\2\2\2\u0175%\3\2\2\2\u0176\u0174"+
		"\3\2\2\2\u0177\u0181\7\66\2\2\u0178\u017d\5(\25\2\u0179\u017a\7+\2\2\u017a"+
		"\u017c\5(\25\2\u017b\u0179\3\2\2\2\u017c\u017f\3\2\2\2\u017d\u017b\3\2"+
		"\2\2\u017d\u017e\3\2\2\2\u017e\u0181\3\2\2\2\u017f\u017d\3\2\2\2\u0180"+
		"\u0177\3\2\2\2\u0180\u0178\3\2\2\2\u0181\'\3\2\2\2\u0182\u018d\5 \21\2"+
		"\u0183\u0184\5.\30\2\u0184\u0185\7\22\2\2\u0185\u0186\5 \21\2\u0186\u0187"+
		"\7\23\2\2\u0187\u018d\3\2\2\2\u0188\u0189\7=\2\2\u0189\u018a\7\22\2\2"+
		"\u018a\u018b\7\66\2\2\u018b\u018d\7\23\2\2\u018c\u0182\3\2\2\2\u018c\u0183"+
		"\3\2\2\2\u018c\u0188\3\2\2\2\u018d)\3\2\2\2\u018e\u0193\7C\2\2\u018f\u0190"+
		"\7+\2\2\u0190\u0192\7C\2\2\u0191\u018f\3\2\2\2\u0192\u0195\3\2\2\2\u0193"+
		"\u0191\3\2\2\2\u0193\u0194\3\2\2\2\u0194+\3\2\2\2\u0195\u0193\3\2\2\2"+
		"\u0196\u0197\t\3\2\2\u0197-\3\2\2\2\u0198\u0199\t\4\2\2\u0199/\3\2\2\2"+
		"\37\63HXh\u0088\u0090\u0095\u009b\u009d\u00c8\u00f0\u00f7\u00fe\u0102"+
		"\u0107\u0110\u011b\u0123\u012a\u0133\u013f\u014f\u0161\u0169\u0174\u017d"+
		"\u0180\u018c\u0193";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}