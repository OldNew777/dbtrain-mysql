// Generated from /home/kasumi/Documents/4thYear1/DatabaseIntro/dbtrain-mysql/src/parser/MYSQL.g4 by ANTLR 4.8
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
		T__52=53, T__53=54, EqualOrAssign=55, Less=56, LessEqual=57, Greater=58, 
		GreaterEqual=59, NotEqual=60, Count=61, Average=62, Max=63, Min=64, Sum=65, 
		Null=66, Date=67, Identifier=68, Integer=69, String=70, Float=71, Whitespace=72, 
		Annotation=73;
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
			"'USE'", "'RENAME'", "'TO'", "'TABLES'", "'INDEXES'", "'LOAD'", "'FROM'", 
			"'FILE'", "'TABLE'", "'DUMP'", "'('", "')'", "'DESC'", "'SHADOW'", "'INSERT'", 
			"'INTO'", "'VALUES'", "'DELETE'", "'WHERE'", "'UPDATE'", "'SET'", "'SELECT'", 
			"'GROUP'", "'BY'", "'LIMIT'", "'OFFSET'", "'ALTER'", "'ADD'", "'INDEX'", 
			"'PRIMARY'", "'KEY'", "'FOREIGN'", "'CONSTRAINT'", "'REFERENCES'", "'UNIQUE'", 
			"','", "'NOT'", "'DEFAULT'", "'INT'", "'VARCHAR'", "'FLOAT'", "'DATE'", 
			"'AND'", "'IS'", "'IN'", "'LIKE'", "'.'", "'*'", "'='", "'<'", "'<='", 
			"'>'", "'>='", "'<>'", "'COUNT'", "'AVG'", "'MAX'", "'MIN'", "'SUM'", 
			"'NULL'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, "EqualOrAssign", "Less", "LessEqual", 
			"Greater", "GreaterEqual", "NotEqual", "Count", "Average", "Max", "Min", 
			"Sum", "Null", "Date", "Identifier", "Integer", "String", "Float", "Whitespace", 
			"Annotation"
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
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__1) | (1L << T__3) | (1L << T__4) | (1L << T__6) | (1L << T__7) | (1L << T__11) | (1L << T__15) | (1L << T__18) | (1L << T__20) | (1L << T__23) | (1L << T__25) | (1L << T__27) | (1L << T__32))) != 0) || _la==Null || _la==Annotation) {
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
	public static class Rename_dbContext extends Db_statementContext {
		public List<TerminalNode> Identifier() { return getTokens(MYSQLParser.Identifier); }
		public TerminalNode Identifier(int i) {
			return getToken(MYSQLParser.Identifier, i);
		}
		public Rename_dbContext(Db_statementContext ctx) { copyFrom(ctx); }
	}
	public static class Show_indexesContext extends Db_statementContext {
		public Show_indexesContext(Db_statementContext ctx) { copyFrom(ctx); }
	}

	public final Db_statementContext db_statement() throws RecognitionException {
		Db_statementContext _localctx = new Db_statementContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_db_statement);
		try {
			setState(91);
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
				_localctx = new Rename_dbContext(_localctx);
				enterOuterAlt(_localctx, 5);
				{
				setState(82);
				match(T__7);
				setState(83);
				match(T__2);
				setState(84);
				match(Identifier);
				setState(85);
				match(T__8);
				setState(86);
				match(Identifier);
				}
				break;
			case 6:
				_localctx = new Show_tablesContext(_localctx);
				enterOuterAlt(_localctx, 6);
				{
				setState(87);
				match(T__4);
				setState(88);
				match(T__9);
				}
				break;
			case 7:
				_localctx = new Show_indexesContext(_localctx);
				enterOuterAlt(_localctx, 7);
				{
				setState(89);
				match(T__4);
				setState(90);
				match(T__10);
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
			setState(107);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__11:
				_localctx = new Load_dataContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(93);
				match(T__11);
				setState(94);
				match(T__12);
				setState(95);
				match(T__13);
				setState(96);
				match(String);
				setState(97);
				match(T__8);
				setState(98);
				match(T__14);
				setState(99);
				match(Identifier);
				}
				break;
			case T__15:
				_localctx = new Dump_dataContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(100);
				match(T__15);
				setState(101);
				match(T__8);
				setState(102);
				match(T__13);
				setState(103);
				match(String);
				setState(104);
				match(T__12);
				setState(105);
				match(T__14);
				setState(106);
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
	public static class Describe_shadow_tableContext extends Table_statementContext {
		public TerminalNode Identifier() { return getToken(MYSQLParser.Identifier, 0); }
		public Describe_shadow_tableContext(Table_statementContext ctx) { copyFrom(ctx); }
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
			setState(142);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,4,_ctx) ) {
			case 1:
				_localctx = new Create_tableContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(109);
				match(T__1);
				setState(110);
				match(T__14);
				setState(111);
				match(Identifier);
				setState(112);
				match(T__16);
				setState(113);
				field_list();
				setState(114);
				match(T__17);
				}
				break;
			case 2:
				_localctx = new Drop_tableContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(116);
				match(T__3);
				setState(117);
				match(T__14);
				setState(118);
				match(Identifier);
				}
				break;
			case 3:
				_localctx = new Describe_tableContext(_localctx);
				enterOuterAlt(_localctx, 3);
				{
				setState(119);
				match(T__18);
				setState(120);
				match(Identifier);
				}
				break;
			case 4:
				_localctx = new Describe_shadow_tableContext(_localctx);
				enterOuterAlt(_localctx, 4);
				{
				setState(121);
				match(T__18);
				setState(122);
				match(T__19);
				setState(123);
				match(Identifier);
				}
				break;
			case 5:
				_localctx = new Insert_into_tableContext(_localctx);
				enterOuterAlt(_localctx, 5);
				{
				setState(124);
				match(T__20);
				setState(125);
				match(T__21);
				setState(126);
				match(Identifier);
				setState(127);
				match(T__22);
				setState(128);
				value_lists();
				}
				break;
			case 6:
				_localctx = new Delete_from_tableContext(_localctx);
				enterOuterAlt(_localctx, 6);
				{
				setState(129);
				match(T__23);
				setState(130);
				match(T__12);
				setState(131);
				match(Identifier);
				setState(132);
				match(T__24);
				setState(133);
				where_and_clause();
				}
				break;
			case 7:
				_localctx = new Update_tableContext(_localctx);
				enterOuterAlt(_localctx, 7);
				{
				setState(134);
				match(T__25);
				setState(135);
				match(Identifier);
				setState(136);
				match(T__26);
				setState(137);
				set_clause();
				setState(138);
				match(T__24);
				setState(139);
				where_and_clause();
				}
				break;
			case 8:
				_localctx = new Select_table_Context(_localctx);
				enterOuterAlt(_localctx, 8);
				{
				setState(141);
				select_table();
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
			setState(144);
			match(T__27);
			setState(145);
			selectors();
			setState(146);
			match(T__12);
			setState(147);
			identifiers();
			setState(150);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__24) {
				{
				setState(148);
				match(T__24);
				setState(149);
				where_and_clause();
				}
			}

			setState(155);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__28) {
				{
				setState(152);
				match(T__28);
				setState(153);
				match(T__29);
				setState(154);
				column();
				}
			}

			setState(163);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__30) {
				{
				setState(157);
				match(T__30);
				setState(158);
				match(Integer);
				setState(161);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__31) {
					{
					setState(159);
					match(T__31);
					setState(160);
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
	public static class Alter_table_drop_uniqueContext extends Alter_statementContext {
		public TerminalNode Identifier() { return getToken(MYSQLParser.Identifier, 0); }
		public IdentifiersContext identifiers() {
			return getRuleContext(IdentifiersContext.class,0);
		}
		public Alter_table_drop_uniqueContext(Alter_statementContext ctx) { copyFrom(ctx); }
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
			setState(257);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,11,_ctx) ) {
			case 1:
				_localctx = new Alter_add_indexContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(165);
				match(T__32);
				setState(166);
				match(T__14);
				setState(167);
				match(Identifier);
				setState(168);
				match(T__33);
				setState(169);
				match(T__34);
				setState(170);
				match(T__16);
				setState(171);
				identifiers();
				setState(172);
				match(T__17);
				}
				break;
			case 2:
				_localctx = new Alter_drop_indexContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(174);
				match(T__32);
				setState(175);
				match(T__14);
				setState(176);
				match(Identifier);
				setState(177);
				match(T__3);
				setState(178);
				match(T__34);
				setState(179);
				match(T__16);
				setState(180);
				identifiers();
				setState(181);
				match(T__17);
				}
				break;
			case 3:
				_localctx = new Alter_table_drop_pkContext(_localctx);
				enterOuterAlt(_localctx, 3);
				{
				setState(183);
				match(T__32);
				setState(184);
				match(T__14);
				setState(185);
				match(Identifier);
				setState(186);
				match(T__3);
				setState(187);
				match(T__35);
				setState(188);
				match(T__36);
				setState(189);
				match(T__16);
				setState(190);
				identifiers();
				setState(191);
				match(T__17);
				}
				break;
			case 4:
				_localctx = new Alter_table_drop_foreign_keyContext(_localctx);
				enterOuterAlt(_localctx, 4);
				{
				setState(193);
				match(T__32);
				setState(194);
				match(T__14);
				setState(195);
				match(Identifier);
				setState(196);
				match(T__3);
				setState(197);
				match(T__37);
				setState(198);
				match(T__36);
				setState(199);
				match(Identifier);
				}
				break;
			case 5:
				_localctx = new Alter_table_add_pkContext(_localctx);
				enterOuterAlt(_localctx, 5);
				{
				setState(200);
				match(T__32);
				setState(201);
				match(T__14);
				setState(202);
				match(Identifier);
				setState(203);
				match(T__33);
				setState(206);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__38) {
					{
					setState(204);
					match(T__38);
					setState(205);
					match(Identifier);
					}
				}

				setState(208);
				match(T__35);
				setState(209);
				match(T__36);
				setState(210);
				match(T__16);
				setState(211);
				identifiers();
				setState(212);
				match(T__17);
				}
				break;
			case 6:
				_localctx = new Alter_table_add_foreign_keyContext(_localctx);
				enterOuterAlt(_localctx, 6);
				{
				setState(214);
				match(T__32);
				setState(215);
				match(T__14);
				setState(216);
				match(Identifier);
				setState(217);
				match(T__33);
				setState(220);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__38) {
					{
					setState(218);
					match(T__38);
					setState(219);
					match(Identifier);
					}
				}

				setState(222);
				match(T__37);
				setState(223);
				match(T__36);
				setState(224);
				match(T__16);
				setState(225);
				identifiers();
				setState(226);
				match(T__17);
				setState(227);
				match(T__39);
				setState(228);
				match(Identifier);
				setState(229);
				match(T__16);
				setState(230);
				identifiers();
				setState(231);
				match(T__17);
				}
				break;
			case 7:
				_localctx = new Alter_table_add_uniqueContext(_localctx);
				enterOuterAlt(_localctx, 7);
				{
				setState(233);
				match(T__32);
				setState(234);
				match(T__14);
				setState(235);
				match(Identifier);
				setState(236);
				match(T__33);
				setState(237);
				match(T__40);
				setState(238);
				match(T__16);
				setState(239);
				identifiers();
				setState(240);
				match(T__17);
				}
				break;
			case 8:
				_localctx = new Alter_table_drop_uniqueContext(_localctx);
				enterOuterAlt(_localctx, 8);
				{
				setState(242);
				match(T__32);
				setState(243);
				match(T__14);
				setState(244);
				match(Identifier);
				setState(245);
				match(T__3);
				setState(246);
				match(T__40);
				setState(247);
				match(T__16);
				setState(248);
				identifiers();
				setState(249);
				match(T__17);
				}
				break;
			case 9:
				_localctx = new Alter_table_renameContext(_localctx);
				enterOuterAlt(_localctx, 9);
				{
				setState(251);
				match(T__32);
				setState(252);
				match(T__14);
				setState(253);
				match(Identifier);
				setState(254);
				match(T__7);
				setState(255);
				match(T__8);
				setState(256);
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
			setState(259);
			field();
			setState(264);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__41) {
				{
				{
				setState(260);
				match(T__41);
				setState(261);
				field();
				}
				}
				setState(266);
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
			setState(300);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Identifier:
				_localctx = new Normal_fieldContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(267);
				match(Identifier);
				setState(268);
				type_();
				setState(271);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__42) {
					{
					setState(269);
					match(T__42);
					setState(270);
					match(Null);
					}
				}

				setState(275);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__43) {
					{
					setState(273);
					match(T__43);
					setState(274);
					value();
					}
				}

				}
				break;
			case T__35:
				_localctx = new Primary_key_fieldContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(277);
				match(T__35);
				setState(278);
				match(T__36);
				setState(280);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==Identifier) {
					{
					setState(279);
					match(Identifier);
					}
				}

				setState(282);
				match(T__16);
				setState(283);
				identifiers();
				setState(284);
				match(T__17);
				}
				break;
			case T__37:
				_localctx = new Foreign_key_fieldContext(_localctx);
				enterOuterAlt(_localctx, 3);
				{
				setState(286);
				match(T__37);
				setState(287);
				match(T__36);
				setState(289);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==Identifier) {
					{
					setState(288);
					match(Identifier);
					}
				}

				setState(291);
				match(T__16);
				setState(292);
				identifiers();
				setState(293);
				match(T__17);
				setState(294);
				match(T__39);
				setState(295);
				match(Identifier);
				setState(296);
				match(T__16);
				setState(297);
				identifiers();
				setState(298);
				match(T__17);
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
			setState(309);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__44:
				enterOuterAlt(_localctx, 1);
				{
				setState(302);
				match(T__44);
				}
				break;
			case T__45:
				enterOuterAlt(_localctx, 2);
				{
				setState(303);
				match(T__45);
				setState(304);
				match(T__16);
				setState(305);
				match(Integer);
				setState(306);
				match(T__17);
				}
				break;
			case T__46:
				enterOuterAlt(_localctx, 3);
				{
				setState(307);
				match(T__46);
				}
				break;
			case T__47:
				enterOuterAlt(_localctx, 4);
				{
				setState(308);
				match(T__47);
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
			setState(311);
			value_list();
			setState(316);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__41) {
				{
				{
				setState(312);
				match(T__41);
				setState(313);
				value_list();
				}
				}
				setState(318);
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
			setState(319);
			match(T__16);
			setState(320);
			value();
			setState(325);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__41) {
				{
				{
				setState(321);
				match(T__41);
				setState(322);
				value();
				}
				}
				setState(327);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(328);
			match(T__17);
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
		public TerminalNode Date() { return getToken(MYSQLParser.Date, 0); }
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
			setState(330);
			_la = _input.LA(1);
			if ( !(((((_la - 66)) & ~0x3f) == 0 && ((1L << (_la - 66)) & ((1L << (Null - 66)) | (1L << (Date - 66)) | (1L << (Integer - 66)) | (1L << (String - 66)) | (1L << (Float - 66)))) != 0)) ) {
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
			setState(332);
			where_clause();
			setState(337);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__48) {
				{
				{
				setState(333);
				match(T__48);
				setState(334);
				where_clause();
				}
				}
				setState(339);
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
			setState(371);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,23,_ctx) ) {
			case 1:
				_localctx = new Where_operator_expressionContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(340);
				column();
				setState(341);
				operator_();
				setState(342);
				expression();
				}
				break;
			case 2:
				_localctx = new Where_operator_selectContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(344);
				column();
				setState(345);
				operator_();
				setState(346);
				match(T__16);
				setState(347);
				select_table();
				setState(348);
				match(T__17);
				}
				break;
			case 3:
				_localctx = new Where_nullContext(_localctx);
				enterOuterAlt(_localctx, 3);
				{
				setState(350);
				column();
				setState(351);
				match(T__49);
				setState(353);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__42) {
					{
					setState(352);
					match(T__42);
					}
				}

				setState(355);
				match(Null);
				}
				break;
			case 4:
				_localctx = new Where_in_listContext(_localctx);
				enterOuterAlt(_localctx, 4);
				{
				setState(357);
				column();
				setState(358);
				match(T__50);
				setState(359);
				value_list();
				}
				break;
			case 5:
				_localctx = new Where_in_selectContext(_localctx);
				enterOuterAlt(_localctx, 5);
				{
				setState(361);
				column();
				setState(362);
				match(T__50);
				setState(363);
				match(T__16);
				setState(364);
				select_table();
				setState(365);
				match(T__17);
				}
				break;
			case 6:
				_localctx = new Where_like_stringContext(_localctx);
				enterOuterAlt(_localctx, 6);
				{
				setState(367);
				column();
				setState(368);
				match(T__51);
				setState(369);
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
			setState(373);
			match(Identifier);
			setState(374);
			match(T__52);
			setState(375);
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
			setState(379);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Null:
			case Date:
			case Integer:
			case String:
			case Float:
				enterOuterAlt(_localctx, 1);
				{
				setState(377);
				value();
				}
				break;
			case Identifier:
				enterOuterAlt(_localctx, 2);
				{
				setState(378);
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
			setState(381);
			match(Identifier);
			setState(382);
			match(EqualOrAssign);
			setState(383);
			value();
			setState(390);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__41) {
				{
				{
				setState(384);
				match(T__41);
				setState(385);
				match(Identifier);
				setState(386);
				match(EqualOrAssign);
				setState(387);
				value();
				}
				}
				setState(392);
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
			setState(402);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__53:
				enterOuterAlt(_localctx, 1);
				{
				setState(393);
				match(T__53);
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
				setState(394);
				selector();
				setState(399);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==T__41) {
					{
					{
					setState(395);
					match(T__41);
					setState(396);
					selector();
					}
					}
					setState(401);
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
			setState(414);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,28,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(404);
				column();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(405);
				aggregator();
				setState(406);
				match(T__16);
				setState(407);
				column();
				setState(408);
				match(T__17);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(410);
				match(Count);
				setState(411);
				match(T__16);
				setState(412);
				match(T__53);
				setState(413);
				match(T__17);
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
			setState(416);
			match(Identifier);
			setState(421);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__41) {
				{
				{
				setState(417);
				match(T__41);
				setState(418);
				match(Identifier);
				}
				}
				setState(423);
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
			setState(424);
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
			setState(426);
			_la = _input.LA(1);
			if ( !(((((_la - 61)) & ~0x3f) == 0 && ((1L << (_la - 61)) & ((1L << (Count - 61)) | (1L << (Average - 61)) | (1L << (Max - 61)) | (1L << (Min - 61)) | (1L << (Sum - 61)))) != 0)) ) {
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
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\3K\u01af\4\2\t\2\4"+
		"\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13\t"+
		"\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22\t\22"+
		"\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\3\2\7\2\62"+
		"\n\2\f\2\16\2\65\13\2\3\2\3\2\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3"+
		"\3\3\3\3\3\3\3\3\3\3\3\3\5\3I\n\3\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4"+
		"\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\5\4^\n\4\3\5\3\5\3\5\3\5\3\5"+
		"\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\5\5\5n\n\5\3\6\3\6\3\6\3\6\3\6\3\6"+
		"\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3"+
		"\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\5\6\u0091\n\6\3\7\3\7\3\7\3\7\3"+
		"\7\3\7\5\7\u0099\n\7\3\7\3\7\3\7\5\7\u009e\n\7\3\7\3\7\3\7\3\7\5\7\u00a4"+
		"\n\7\5\7\u00a6\n\7\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b"+
		"\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3"+
		"\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\5\b\u00d1\n\b\3\b\3\b\3\b\3"+
		"\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\5\b\u00df\n\b\3\b\3\b\3\b\3\b\3\b\3"+
		"\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b"+
		"\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\5\b\u0104\n\b\3\t\3\t"+
		"\3\t\7\t\u0109\n\t\f\t\16\t\u010c\13\t\3\n\3\n\3\n\3\n\5\n\u0112\n\n\3"+
		"\n\3\n\5\n\u0116\n\n\3\n\3\n\3\n\5\n\u011b\n\n\3\n\3\n\3\n\3\n\3\n\3\n"+
		"\3\n\5\n\u0124\n\n\3\n\3\n\3\n\3\n\3\n\3\n\3\n\3\n\3\n\5\n\u012f\n\n\3"+
		"\13\3\13\3\13\3\13\3\13\3\13\3\13\5\13\u0138\n\13\3\f\3\f\3\f\7\f\u013d"+
		"\n\f\f\f\16\f\u0140\13\f\3\r\3\r\3\r\3\r\7\r\u0146\n\r\f\r\16\r\u0149"+
		"\13\r\3\r\3\r\3\16\3\16\3\17\3\17\3\17\7\17\u0152\n\17\f\17\16\17\u0155"+
		"\13\17\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20"+
		"\5\20\u0164\n\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20"+
		"\3\20\3\20\3\20\3\20\3\20\5\20\u0176\n\20\3\21\3\21\3\21\3\21\3\22\3\22"+
		"\5\22\u017e\n\22\3\23\3\23\3\23\3\23\3\23\3\23\3\23\7\23\u0187\n\23\f"+
		"\23\16\23\u018a\13\23\3\24\3\24\3\24\3\24\7\24\u0190\n\24\f\24\16\24\u0193"+
		"\13\24\5\24\u0195\n\24\3\25\3\25\3\25\3\25\3\25\3\25\3\25\3\25\3\25\3"+
		"\25\5\25\u01a1\n\25\3\26\3\26\3\26\7\26\u01a6\n\26\f\26\16\26\u01a9\13"+
		"\26\3\27\3\27\3\30\3\30\3\30\2\2\31\2\4\6\b\n\f\16\20\22\24\26\30\32\34"+
		"\36 \"$&(*,.\2\5\4\2DEGI\3\29>\3\2?C\2\u01d3\2\63\3\2\2\2\4H\3\2\2\2\6"+
		"]\3\2\2\2\bm\3\2\2\2\n\u0090\3\2\2\2\f\u0092\3\2\2\2\16\u0103\3\2\2\2"+
		"\20\u0105\3\2\2\2\22\u012e\3\2\2\2\24\u0137\3\2\2\2\26\u0139\3\2\2\2\30"+
		"\u0141\3\2\2\2\32\u014c\3\2\2\2\34\u014e\3\2\2\2\36\u0175\3\2\2\2 \u0177"+
		"\3\2\2\2\"\u017d\3\2\2\2$\u017f\3\2\2\2&\u0194\3\2\2\2(\u01a0\3\2\2\2"+
		"*\u01a2\3\2\2\2,\u01aa\3\2\2\2.\u01ac\3\2\2\2\60\62\5\4\3\2\61\60\3\2"+
		"\2\2\62\65\3\2\2\2\63\61\3\2\2\2\63\64\3\2\2\2\64\66\3\2\2\2\65\63\3\2"+
		"\2\2\66\67\7\2\2\3\67\3\3\2\2\289\5\6\4\29:\7\3\2\2:I\3\2\2\2;<\5\b\5"+
		"\2<=\7\3\2\2=I\3\2\2\2>?\5\n\6\2?@\7\3\2\2@I\3\2\2\2AB\5\16\b\2BC\7\3"+
		"\2\2CI\3\2\2\2DE\7K\2\2EI\7\3\2\2FG\7D\2\2GI\7\3\2\2H8\3\2\2\2H;\3\2\2"+
		"\2H>\3\2\2\2HA\3\2\2\2HD\3\2\2\2HF\3\2\2\2I\5\3\2\2\2JK\7\4\2\2KL\7\5"+
		"\2\2L^\7F\2\2MN\7\6\2\2NO\7\5\2\2O^\7F\2\2PQ\7\7\2\2Q^\7\b\2\2RS\7\t\2"+
		"\2S^\7F\2\2TU\7\n\2\2UV\7\5\2\2VW\7F\2\2WX\7\13\2\2X^\7F\2\2YZ\7\7\2\2"+
		"Z^\7\f\2\2[\\\7\7\2\2\\^\7\r\2\2]J\3\2\2\2]M\3\2\2\2]P\3\2\2\2]R\3\2\2"+
		"\2]T\3\2\2\2]Y\3\2\2\2][\3\2\2\2^\7\3\2\2\2_`\7\16\2\2`a\7\17\2\2ab\7"+
		"\20\2\2bc\7H\2\2cd\7\13\2\2de\7\21\2\2en\7F\2\2fg\7\22\2\2gh\7\13\2\2"+
		"hi\7\20\2\2ij\7H\2\2jk\7\17\2\2kl\7\21\2\2ln\7F\2\2m_\3\2\2\2mf\3\2\2"+
		"\2n\t\3\2\2\2op\7\4\2\2pq\7\21\2\2qr\7F\2\2rs\7\23\2\2st\5\20\t\2tu\7"+
		"\24\2\2u\u0091\3\2\2\2vw\7\6\2\2wx\7\21\2\2x\u0091\7F\2\2yz\7\25\2\2z"+
		"\u0091\7F\2\2{|\7\25\2\2|}\7\26\2\2}\u0091\7F\2\2~\177\7\27\2\2\177\u0080"+
		"\7\30\2\2\u0080\u0081\7F\2\2\u0081\u0082\7\31\2\2\u0082\u0091\5\26\f\2"+
		"\u0083\u0084\7\32\2\2\u0084\u0085\7\17\2\2\u0085\u0086\7F\2\2\u0086\u0087"+
		"\7\33\2\2\u0087\u0091\5\34\17\2\u0088\u0089\7\34\2\2\u0089\u008a\7F\2"+
		"\2\u008a\u008b\7\35\2\2\u008b\u008c\5$\23\2\u008c\u008d\7\33\2\2\u008d"+
		"\u008e\5\34\17\2\u008e\u0091\3\2\2\2\u008f\u0091\5\f\7\2\u0090o\3\2\2"+
		"\2\u0090v\3\2\2\2\u0090y\3\2\2\2\u0090{\3\2\2\2\u0090~\3\2\2\2\u0090\u0083"+
		"\3\2\2\2\u0090\u0088\3\2\2\2\u0090\u008f\3\2\2\2\u0091\13\3\2\2\2\u0092"+
		"\u0093\7\36\2\2\u0093\u0094\5&\24\2\u0094\u0095\7\17\2\2\u0095\u0098\5"+
		"*\26\2\u0096\u0097\7\33\2\2\u0097\u0099\5\34\17\2\u0098\u0096\3\2\2\2"+
		"\u0098\u0099\3\2\2\2\u0099\u009d\3\2\2\2\u009a\u009b\7\37\2\2\u009b\u009c"+
		"\7 \2\2\u009c\u009e\5 \21\2\u009d\u009a\3\2\2\2\u009d\u009e\3\2\2\2\u009e"+
		"\u00a5\3\2\2\2\u009f\u00a0\7!\2\2\u00a0\u00a3\7G\2\2\u00a1\u00a2\7\"\2"+
		"\2\u00a2\u00a4\7G\2\2\u00a3\u00a1\3\2\2\2\u00a3\u00a4\3\2\2\2\u00a4\u00a6"+
		"\3\2\2\2\u00a5\u009f\3\2\2\2\u00a5\u00a6\3\2\2\2\u00a6\r\3\2\2\2\u00a7"+
		"\u00a8\7#\2\2\u00a8\u00a9\7\21\2\2\u00a9\u00aa\7F\2\2\u00aa\u00ab\7$\2"+
		"\2\u00ab\u00ac\7%\2\2\u00ac\u00ad\7\23\2\2\u00ad\u00ae\5*\26\2\u00ae\u00af"+
		"\7\24\2\2\u00af\u0104\3\2\2\2\u00b0\u00b1\7#\2\2\u00b1\u00b2\7\21\2\2"+
		"\u00b2\u00b3\7F\2\2\u00b3\u00b4\7\6\2\2\u00b4\u00b5\7%\2\2\u00b5\u00b6"+
		"\7\23\2\2\u00b6\u00b7\5*\26\2\u00b7\u00b8\7\24\2\2\u00b8\u0104\3\2\2\2"+
		"\u00b9\u00ba\7#\2\2\u00ba\u00bb\7\21\2\2\u00bb\u00bc\7F\2\2\u00bc\u00bd"+
		"\7\6\2\2\u00bd\u00be\7&\2\2\u00be\u00bf\7\'\2\2\u00bf\u00c0\7\23\2\2\u00c0"+
		"\u00c1\5*\26\2\u00c1\u00c2\7\24\2\2\u00c2\u0104\3\2\2\2\u00c3\u00c4\7"+
		"#\2\2\u00c4\u00c5\7\21\2\2\u00c5\u00c6\7F\2\2\u00c6\u00c7\7\6\2\2\u00c7"+
		"\u00c8\7(\2\2\u00c8\u00c9\7\'\2\2\u00c9\u0104\7F\2\2\u00ca\u00cb\7#\2"+
		"\2\u00cb\u00cc\7\21\2\2\u00cc\u00cd\7F\2\2\u00cd\u00d0\7$\2\2\u00ce\u00cf"+
		"\7)\2\2\u00cf\u00d1\7F\2\2\u00d0\u00ce\3\2\2\2\u00d0\u00d1\3\2\2\2\u00d1"+
		"\u00d2\3\2\2\2\u00d2\u00d3\7&\2\2\u00d3\u00d4\7\'\2\2\u00d4\u00d5\7\23"+
		"\2\2\u00d5\u00d6\5*\26\2\u00d6\u00d7\7\24\2\2\u00d7\u0104\3\2\2\2\u00d8"+
		"\u00d9\7#\2\2\u00d9\u00da\7\21\2\2\u00da\u00db\7F\2\2\u00db\u00de\7$\2"+
		"\2\u00dc\u00dd\7)\2\2\u00dd\u00df\7F\2\2\u00de\u00dc\3\2\2\2\u00de\u00df"+
		"\3\2\2\2\u00df\u00e0\3\2\2\2\u00e0\u00e1\7(\2\2\u00e1\u00e2\7\'\2\2\u00e2"+
		"\u00e3\7\23\2\2\u00e3\u00e4\5*\26\2\u00e4\u00e5\7\24\2\2\u00e5\u00e6\7"+
		"*\2\2\u00e6\u00e7\7F\2\2\u00e7\u00e8\7\23\2\2\u00e8\u00e9\5*\26\2\u00e9"+
		"\u00ea\7\24\2\2\u00ea\u0104\3\2\2\2\u00eb\u00ec\7#\2\2\u00ec\u00ed\7\21"+
		"\2\2\u00ed\u00ee\7F\2\2\u00ee\u00ef\7$\2\2\u00ef\u00f0\7+\2\2\u00f0\u00f1"+
		"\7\23\2\2\u00f1\u00f2\5*\26\2\u00f2\u00f3\7\24\2\2\u00f3\u0104\3\2\2\2"+
		"\u00f4\u00f5\7#\2\2\u00f5\u00f6\7\21\2\2\u00f6\u00f7\7F\2\2\u00f7\u00f8"+
		"\7\6\2\2\u00f8\u00f9\7+\2\2\u00f9\u00fa\7\23\2\2\u00fa\u00fb\5*\26\2\u00fb"+
		"\u00fc\7\24\2\2\u00fc\u0104\3\2\2\2\u00fd\u00fe\7#\2\2\u00fe\u00ff\7\21"+
		"\2\2\u00ff\u0100\7F\2\2\u0100\u0101\7\n\2\2\u0101\u0102\7\13\2\2\u0102"+
		"\u0104\7F\2\2\u0103\u00a7\3\2\2\2\u0103\u00b0\3\2\2\2\u0103\u00b9\3\2"+
		"\2\2\u0103\u00c3\3\2\2\2\u0103\u00ca\3\2\2\2\u0103\u00d8\3\2\2\2\u0103"+
		"\u00eb\3\2\2\2\u0103\u00f4\3\2\2\2\u0103\u00fd\3\2\2\2\u0104\17\3\2\2"+
		"\2\u0105\u010a\5\22\n\2\u0106\u0107\7,\2\2\u0107\u0109\5\22\n\2\u0108"+
		"\u0106\3\2\2\2\u0109\u010c\3\2\2\2\u010a\u0108\3\2\2\2\u010a\u010b\3\2"+
		"\2\2\u010b\21\3\2\2\2\u010c\u010a\3\2\2\2\u010d\u010e\7F\2\2\u010e\u0111"+
		"\5\24\13\2\u010f\u0110\7-\2\2\u0110\u0112\7D\2\2\u0111\u010f\3\2\2\2\u0111"+
		"\u0112\3\2\2\2\u0112\u0115\3\2\2\2\u0113\u0114\7.\2\2\u0114\u0116\5\32"+
		"\16\2\u0115\u0113\3\2\2\2\u0115\u0116\3\2\2\2\u0116\u012f\3\2\2\2\u0117"+
		"\u0118\7&\2\2\u0118\u011a\7\'\2\2\u0119\u011b\7F\2\2\u011a\u0119\3\2\2"+
		"\2\u011a\u011b\3\2\2\2\u011b\u011c\3\2\2\2\u011c\u011d\7\23\2\2\u011d"+
		"\u011e\5*\26\2\u011e\u011f\7\24\2\2\u011f\u012f\3\2\2\2\u0120\u0121\7"+
		"(\2\2\u0121\u0123\7\'\2\2\u0122\u0124\7F\2\2\u0123\u0122\3\2\2\2\u0123"+
		"\u0124\3\2\2\2\u0124\u0125\3\2\2\2\u0125\u0126\7\23\2\2\u0126\u0127\5"+
		"*\26\2\u0127\u0128\7\24\2\2\u0128\u0129\7*\2\2\u0129\u012a\7F\2\2\u012a"+
		"\u012b\7\23\2\2\u012b\u012c\5*\26\2\u012c\u012d\7\24\2\2\u012d\u012f\3"+
		"\2\2\2\u012e\u010d\3\2\2\2\u012e\u0117\3\2\2\2\u012e\u0120\3\2\2\2\u012f"+
		"\23\3\2\2\2\u0130\u0138\7/\2\2\u0131\u0132\7\60\2\2\u0132\u0133\7\23\2"+
		"\2\u0133\u0134\7G\2\2\u0134\u0138\7\24\2\2\u0135\u0138\7\61\2\2\u0136"+
		"\u0138\7\62\2\2\u0137\u0130\3\2\2\2\u0137\u0131\3\2\2\2\u0137\u0135\3"+
		"\2\2\2\u0137\u0136\3\2\2\2\u0138\25\3\2\2\2\u0139\u013e\5\30\r\2\u013a"+
		"\u013b\7,\2\2\u013b\u013d\5\30\r\2\u013c\u013a\3\2\2\2\u013d\u0140\3\2"+
		"\2\2\u013e\u013c\3\2\2\2\u013e\u013f\3\2\2\2\u013f\27\3\2\2\2\u0140\u013e"+
		"\3\2\2\2\u0141\u0142\7\23\2\2\u0142\u0147\5\32\16\2\u0143\u0144\7,\2\2"+
		"\u0144\u0146\5\32\16\2\u0145\u0143\3\2\2\2\u0146\u0149\3\2\2\2\u0147\u0145"+
		"\3\2\2\2\u0147\u0148\3\2\2\2\u0148\u014a\3\2\2\2\u0149\u0147\3\2\2\2\u014a"+
		"\u014b\7\24\2\2\u014b\31\3\2\2\2\u014c\u014d\t\2\2\2\u014d\33\3\2\2\2"+
		"\u014e\u0153\5\36\20\2\u014f\u0150\7\63\2\2\u0150\u0152\5\36\20\2\u0151"+
		"\u014f\3\2\2\2\u0152\u0155\3\2\2\2\u0153\u0151\3\2\2\2\u0153\u0154\3\2"+
		"\2\2\u0154\35\3\2\2\2\u0155\u0153\3\2\2\2\u0156\u0157\5 \21\2\u0157\u0158"+
		"\5,\27\2\u0158\u0159\5\"\22\2\u0159\u0176\3\2\2\2\u015a\u015b\5 \21\2"+
		"\u015b\u015c\5,\27\2\u015c\u015d\7\23\2\2\u015d\u015e\5\f\7\2\u015e\u015f"+
		"\7\24\2\2\u015f\u0176\3\2\2\2\u0160\u0161\5 \21\2\u0161\u0163\7\64\2\2"+
		"\u0162\u0164\7-\2\2\u0163\u0162\3\2\2\2\u0163\u0164\3\2\2\2\u0164\u0165"+
		"\3\2\2\2\u0165\u0166\7D\2\2\u0166\u0176\3\2\2\2\u0167\u0168\5 \21\2\u0168"+
		"\u0169\7\65\2\2\u0169\u016a\5\30\r\2\u016a\u0176\3\2\2\2\u016b\u016c\5"+
		" \21\2\u016c\u016d\7\65\2\2\u016d\u016e\7\23\2\2\u016e\u016f\5\f\7\2\u016f"+
		"\u0170\7\24\2\2\u0170\u0176\3\2\2\2\u0171\u0172\5 \21\2\u0172\u0173\7"+
		"\66\2\2\u0173\u0174\7H\2\2\u0174\u0176\3\2\2\2\u0175\u0156\3\2\2\2\u0175"+
		"\u015a\3\2\2\2\u0175\u0160\3\2\2\2\u0175\u0167\3\2\2\2\u0175\u016b\3\2"+
		"\2\2\u0175\u0171\3\2\2\2\u0176\37\3\2\2\2\u0177\u0178\7F\2\2\u0178\u0179"+
		"\7\67\2\2\u0179\u017a\7F\2\2\u017a!\3\2\2\2\u017b\u017e\5\32\16\2\u017c"+
		"\u017e\5 \21\2\u017d\u017b\3\2\2\2\u017d\u017c\3\2\2\2\u017e#\3\2\2\2"+
		"\u017f\u0180\7F\2\2\u0180\u0181\79\2\2\u0181\u0188\5\32\16\2\u0182\u0183"+
		"\7,\2\2\u0183\u0184\7F\2\2\u0184\u0185\79\2\2\u0185\u0187\5\32\16\2\u0186"+
		"\u0182\3\2\2\2\u0187\u018a\3\2\2\2\u0188\u0186\3\2\2\2\u0188\u0189\3\2"+
		"\2\2\u0189%\3\2\2\2\u018a\u0188\3\2\2\2\u018b\u0195\78\2\2\u018c\u0191"+
		"\5(\25\2\u018d\u018e\7,\2\2\u018e\u0190\5(\25\2\u018f\u018d\3\2\2\2\u0190"+
		"\u0193\3\2\2\2\u0191\u018f\3\2\2\2\u0191\u0192\3\2\2\2\u0192\u0195\3\2"+
		"\2\2\u0193\u0191\3\2\2\2\u0194\u018b\3\2\2\2\u0194\u018c\3\2\2\2\u0195"+
		"\'\3\2\2\2\u0196\u01a1\5 \21\2\u0197\u0198\5.\30\2\u0198\u0199\7\23\2"+
		"\2\u0199\u019a\5 \21\2\u019a\u019b\7\24\2\2\u019b\u01a1\3\2\2\2\u019c"+
		"\u019d\7?\2\2\u019d\u019e\7\23\2\2\u019e\u019f\78\2\2\u019f\u01a1\7\24"+
		"\2\2\u01a0\u0196\3\2\2\2\u01a0\u0197\3\2\2\2\u01a0\u019c\3\2\2\2\u01a1"+
		")\3\2\2\2\u01a2\u01a7\7F\2\2\u01a3\u01a4\7,\2\2\u01a4\u01a6\7F\2\2\u01a5"+
		"\u01a3\3\2\2\2\u01a6\u01a9\3\2\2\2\u01a7\u01a5\3\2\2\2\u01a7\u01a8\3\2"+
		"\2\2\u01a8+\3\2\2\2\u01a9\u01a7\3\2\2\2\u01aa\u01ab\t\3\2\2\u01ab-\3\2"+
		"\2\2\u01ac\u01ad\t\4\2\2\u01ad/\3\2\2\2 \63H]m\u0090\u0098\u009d\u00a3"+
		"\u00a5\u00d0\u00de\u0103\u010a\u0111\u0115\u011a\u0123\u012e\u0137\u013e"+
		"\u0147\u0153\u0163\u0175\u017d\u0188\u0191\u0194\u01a0\u01a7";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}