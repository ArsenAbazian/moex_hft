using System;
using System.IO;
using System.Collections.Generic;
using System.Text;
using System.Linq;
using System.Xml;
using Mono.Options;
using System.Collections;

namespace prebuild {
	public enum GeneratorMode { 
		Asts,
		Spectra
	}
	class FastTemplatesCodeGenerator {
		List<string> Strings { get { return CurrentFile.Lines; } }

		public bool WriteConstantCheckingCode { get; set; }

		public string RobotCpp { get; set; }
		public string ManagerSourceFileH { get; set; }
		public string ManagerSourceFileCpp { get; set; }
		public string SourceTypes { get; set; }
		public string AstsServerConfigFileName { get; set; }
		public string SpectraServerConfigFileName { get; set; }
		public string AstsTemplateFile { get; set; }
		public string SpectraTemplateFile { get; set; }

		protected TextFile RobotCppFile { get; set; }
		protected TextFile ManagerHFile { get; set; }
		protected TextFile ManagerCppFile { get; set; }
		protected TextFile TypesFile { get; set; }
		protected TextFile CurrentFile { get; set; }

		void WriteLine (string line) { 
			if(CurrentFile == null)
				CurrentFile = ManagerHFile;
			CurrentFile.Add(line);
		}

		protected XmlNode TemplatesNode { get; private set; }
		protected string Prefix { get; private set; }
		protected GeneratorMode Mode { get; private set; }

		string ConstStr(string str) {
			return "\"" + str + "\"";
		}
		string NodeValue(XmlNode node) {
			if(node.ChildNodes.Count == 0 || node.ChildNodes[0].Value == null)
				return "";
			return node.ChildNodes[0].Value.ToString();
		}
		public bool GenerateAddChannelsCode_ASTS() {
			Console.WriteLine("generate add channels code...");

			XmlDocument doc = new XmlDocument();
			//Console.WriteLine("load condif test xml '" + ServerConfigFileName + "'");
			doc.Load(AstsServerConfigFileName);

			SetPosition(AddDefaultChannels_GeneratedCode);
			XmlNode parent = null;
			foreach(XmlNode nd in doc.ChildNodes) {
				if(nd.Name == "configuration") {
					parent = nd;
					break;
				}
			}

			foreach(XmlNode node in parent.ChildNodes) {
				string channelName = node.Attributes["id"].Value;
				string channelLabel = node.Attributes["label"].Value;
				string channelNameUpper = channelName.Substring(0, 1).ToUpper() + channelName.Substring(1).ToLower();

				WriteLine("\tif(this->Allow" + channelNameUpper + "Market()) {");
				WriteLine("\t\tFeedChannel *" + channelName.ToLower() + " = new FeedChannel(" + ConstStr(channelName) + ", " + ConstStr(channelLabel) + ");");
				WriteLine("");
				XmlNode connections = node.ChildNodes[0];
				foreach(XmlNode conn in connections.ChildNodes) {
					string c_id = conn.Attributes["id"].Value;
					string feedType = conn.ChildNodes[0].Attributes["feed-type"].Value;
					string protocol = NodeValue(conn.ChildNodes[1]);

					string protocolValue = protocol == "TCP/IP" ? "FeedConnectionProtocol::TCP_IP" : "FeedConnectionProtocol::UDP_IP";
					string feedValueName = c_id.ToLower() + "_" + channelName.ToLower();
					string feedClassName = "FeedConnection_" + channelName + "_" + c_id;
					string feedValue = "'" + NodeValue(conn.ChildNodes[0]) + "'";

					WriteLine("\t\tif(this->AllowFeed(\"" + c_id + "\")) {");
					if(c_id == "H") {
						string ip = NodeValue(conn.ChildNodes[2]);
						string port = NodeValue(conn.ChildNodes[3]);

						WriteLine("\t\t\tFeedConnection *" + feedValueName + " = new " + feedClassName + "(" + ConstStr(c_id) + ", " + ConstStr(feedType) + ", " + feedValue + ", " + protocolValue + ", " + ConstStr(ip) + ", " + port + ");");
					} else {
						string srcIpA = NodeValue(conn.ChildNodes[2].ChildNodes[0]);
						string ipA = NodeValue(conn.ChildNodes[2].ChildNodes[1]);
						string portA = NodeValue(conn.ChildNodes[2].ChildNodes[2]);

						string srcIpB = NodeValue(conn.ChildNodes[3].ChildNodes[0]);
						string ipB = NodeValue(conn.ChildNodes[3].ChildNodes[1]);
						string portB = NodeValue(conn.ChildNodes[3].ChildNodes[2]);
					
						WriteLine("\t\t\tFeedConnection *" + feedValueName + " = new " + feedClassName + "(" + ConstStr(c_id) + ", " + ConstStr(feedType) + ", " + feedValue + ", " + protocolValue + ", " +
							ConstStr(srcIpA) + ", " + ConstStr(ipA) + ", " + portA + ", " + 
							ConstStr(srcIpB) + ", " + ConstStr(ipB) + ", " + portB +  
							");");
					}
					WriteLine("\t\t\t" + channelName.ToLower() + "->SetConnection(" + feedValueName + ");");
					WriteLine("\t\t}");
				}
				WriteLine("");
				WriteLine("\t\tthis->AddChannel(" + channelName.ToLower() + ");");
				WriteLine("\t}");
			}
			return true;
		}

		protected XmlNode GetTemplatesNode(XmlDocument doc) {
			foreach(XmlNode node in doc.ChildNodes) {
				if(node.Name == "templates")
					return node;
			}
			return null;
		}

		public bool Generate () {
			if(!File.Exists(ManagerSourceFileH)) {
				Console.WriteLine("source file '" + ManagerSourceFileH + "' does not exist.");
				return false;
			}
			if(!File.Exists(ManagerSourceFileCpp)) {
				Console.WriteLine("source file '" + ManagerSourceFileCpp + "' does not exist.");
				return false;
			}
			if(!File.Exists(SourceTypes)) {
				Console.WriteLine("asts source file '" + TypesFile + "' does not exist.");
				return false;
			}
			if(!File.Exists(AstsTemplateFile)) {
				Console.WriteLine("asts template xml file'" + AstsTemplateFile + "' does not exist.");
				return false;
			}
			if(!File.Exists(RobotCpp)) {
				Console.WriteLine("robot source file '" + RobotCpp + "' does not exist.");
				return false;
			}
			if(!File.Exists(AstsServerConfigFileName)) {
				Console.WriteLine("asts server config file '" + AstsServerConfigFileName + "' does not exist.");
			}

			ManagerHFile = new TextFile();
			ManagerCppFile = new TextFile();
			TypesFile = new TextFile();
			RobotCppFile = new TextFile();

			ManagerHFile.LoadFromFile(ManagerSourceFileH);
			ManagerCppFile.LoadFromFile(ManagerSourceFileCpp);
			TypesFile.LoadFromFile(SourceTypes);
			RobotCppFile.LoadFromFile(RobotCpp);

			ClearPreviouseGeneratedCode();

			GenerateMethodsPointerDeclarationCode();
			GenerateDefinesCode();

			Generate_ASTS();
			Generate_Spectra();

			CheckSaveGeneratedFiles();

			return true;
		}

		void GenerateDefinesCode() {
			ClearRegion("Defines_GeneratedCode");
			SetPosition("Defines_GeneratedCode");

			WriteLine("#define PRESENCE_MAP_INDEX0  0x0000000000000040L");
			WriteLine("#define PRESENCE_MAP_INDEX1  0x0000000000000020L");
			WriteLine("#define PRESENCE_MAP_INDEX2  0x0000000000000010L");
			WriteLine("#define PRESENCE_MAP_INDEX3  0x0000000000000008L");
			WriteLine("#define PRESENCE_MAP_INDEX4  0x0000000000000004L");
			WriteLine("#define PRESENCE_MAP_INDEX5  0x0000000000000002L");
			WriteLine("#define PRESENCE_MAP_INDEX6  0x0000000000000001L");

			WriteLine("#define PRESENCE_MAP_INDEX7  0x0000000000004000L");
			WriteLine("#define PRESENCE_MAP_INDEX8  0x0000000000002000L");
			WriteLine("#define PRESENCE_MAP_INDEX9  0x0000000000001000L");
			WriteLine("#define PRESENCE_MAP_INDEX10 0x0000000000000800L");
			WriteLine("#define PRESENCE_MAP_INDEX11 0x0000000000000400L");
			WriteLine("#define PRESENCE_MAP_INDEX12 0x0000000000000200L");
			WriteLine("#define PRESENCE_MAP_INDEX13 0x0000000000000100L");

			WriteLine("#define PRESENCE_MAP_INDEX14 0x0000000000400000L");
			WriteLine("#define PRESENCE_MAP_INDEX15 0x0000000000200000L");
			WriteLine("#define PRESENCE_MAP_INDEX16 0x0000000000100000L");
			WriteLine("#define PRESENCE_MAP_INDEX17 0x0000000000080000L");
			WriteLine("#define PRESENCE_MAP_INDEX18 0x0000000000040000L");
			WriteLine("#define PRESENCE_MAP_INDEX19 0x0000000000020000L");
			WriteLine("#define PRESENCE_MAP_INDEX20 0x0000000000010000L");

			WriteLine("#define PRESENCE_MAP_INDEX21 0x0000000040000000L");
			WriteLine("#define PRESENCE_MAP_INDEX22 0x0000000020000000L");
			WriteLine("#define PRESENCE_MAP_INDEX23 0x0000000010000000L");
			WriteLine("#define PRESENCE_MAP_INDEX24 0x0000000008000000L");
			WriteLine("#define PRESENCE_MAP_INDEX25 0x0000000004000000L");
			WriteLine("#define PRESENCE_MAP_INDEX26 0x0000000002000000L");
			WriteLine("#define PRESENCE_MAP_INDEX27 0x0000000001000000L");

			WriteLine("#define PRESENCE_MAP_INDEX28 0x0000004000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX29 0x0000002000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX30 0x0000001000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX31 0x0000000800000000L");
			WriteLine("#define PRESENCE_MAP_INDEX32 0x0000000400000000L");
			WriteLine("#define PRESENCE_MAP_INDEX33 0x0000000200000000L");
			WriteLine("#define PRESENCE_MAP_INDEX34 0x0000000100000000L");

			WriteLine("#define PRESENCE_MAP_INDEX35 0x0000400000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX36 0x0000200000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX37 0x0000100000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX38 0x0000080000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX39 0x0000040000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX40 0x0000020000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX41 0x0000010000000000L");

			WriteLine("#define PRESENCE_MAP_INDEX42 0x0040000000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX43 0x0020000000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX44 0x0010000000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX45 0x0008000000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX46 0x0004000000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX47 0x0002000000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX48 0x0001000000000000L");

			WriteLine("#define PRESENCE_MAP_INDEX49 0x4000000000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX50 0x2000000000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX51 0x1000000000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX52 0x0800000000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX53 0x0400000000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX54 0x0200000000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX55 0x0100000000000000L");

			WriteLine("#define NULL_MAP_INDEX0      0x0000000000000001L");
			WriteLine("#define NULL_MAP_INDEX1      0x0000000000000002L");
			WriteLine("#define NULL_MAP_INDEX2      0x0000000000000004L");
			WriteLine("#define NULL_MAP_INDEX3      0x0000000000000008L");
			WriteLine("#define NULL_MAP_INDEX4      0x0000000000000010L");
			WriteLine("#define NULL_MAP_INDEX5      0x0000000000000020L");
			WriteLine("#define NULL_MAP_INDEX6      0x0000000000000040L");
			WriteLine("#define NULL_MAP_INDEX7      0x0000000000000080L");
			WriteLine("#define NULL_MAP_INDEX8      0x0000000000000100L");
			WriteLine("#define NULL_MAP_INDEX9      0x0000000000000200L");
			WriteLine("#define NULL_MAP_INDEX10     0x0000000000000400L");
			WriteLine("#define NULL_MAP_INDEX11     0x0000000000000800L");
			WriteLine("#define NULL_MAP_INDEX12     0x0000000000001000L");
			WriteLine("#define NULL_MAP_INDEX13     0x0000000000002000L");
			WriteLine("#define NULL_MAP_INDEX14     0x0000000000004000L");
			WriteLine("#define NULL_MAP_INDEX15     0x0000000000008000L");

			WriteLine("#define NULL_MAP_INDEX16     0x0000000000010000L");
			WriteLine("#define NULL_MAP_INDEX17     0x0000000000020000L");
			WriteLine("#define NULL_MAP_INDEX18     0x0000000000040000L");
			WriteLine("#define NULL_MAP_INDEX19     0x0000000000080000L");
			WriteLine("#define NULL_MAP_INDEX20     0x0000000000100000L");
			WriteLine("#define NULL_MAP_INDEX21     0x0000000000200000L");
			WriteLine("#define NULL_MAP_INDEX22     0x0000000000400000L");
			WriteLine("#define NULL_MAP_INDEX23     0x0000000000800000L");
			WriteLine("#define NULL_MAP_INDEX24     0x0000000001000000L");
			WriteLine("#define NULL_MAP_INDEX25     0x0000000002000000L");
			WriteLine("#define NULL_MAP_INDEX26     0x0000000004000000L");
			WriteLine("#define NULL_MAP_INDEX27     0x0000000008000000L");
			WriteLine("#define NULL_MAP_INDEX28     0x0000000010000000L");
			WriteLine("#define NULL_MAP_INDEX29     0x0000000020000000L");
			WriteLine("#define NULL_MAP_INDEX30     0x0000000040000000L");
			WriteLine("#define NULL_MAP_INDEX31     0x0000000080000000L");

			WriteLine("#define NULL_MAP_INDEX32     0x0000000100000000L");
			WriteLine("#define NULL_MAP_INDEX33     0x0000000200000000L");
			WriteLine("#define NULL_MAP_INDEX34     0x0000000400000000L");
			WriteLine("#define NULL_MAP_INDEX35     0x0000000800000000L");
			WriteLine("#define NULL_MAP_INDEX36     0x0000001000000000L");
			WriteLine("#define NULL_MAP_INDEX37     0x0000002000000000L");
			WriteLine("#define NULL_MAP_INDEX38     0x0000004000000000L");
			WriteLine("#define NULL_MAP_INDEX39     0x0000008000000000L");
			WriteLine("#define NULL_MAP_INDEX40     0x0000010000000000L");
			WriteLine("#define NULL_MAP_INDEX41     0x0000020000000000L");
			WriteLine("#define NULL_MAP_INDEX42     0x0000040000000000L");
			WriteLine("#define NULL_MAP_INDEX43     0x0000080000000000L");
			WriteLine("#define NULL_MAP_INDEX44     0x0000100000000000L");
			WriteLine("#define NULL_MAP_INDEX45     0x0000200000000000L");
			WriteLine("#define NULL_MAP_INDEX46     0x0000400000000000L");
			WriteLine("#define NULL_MAP_INDEX47     0x0000800000000000L");

			WriteLine("#define NULL_MAP_INDEX48     0x0001000000000000L");
			WriteLine("#define NULL_MAP_INDEX49     0x0002000000000000L");
			WriteLine("#define NULL_MAP_INDEX50     0x0004000000000000L");
			WriteLine("#define NULL_MAP_INDEX51     0x0008000000000000L");
			WriteLine("#define NULL_MAP_INDEX52     0x0010000000000000L");
			WriteLine("#define NULL_MAP_INDEX53     0x0020000000000000L");
			WriteLine("#define NULL_MAP_INDEX54     0x0040000000000000L");
			WriteLine("#define NULL_MAP_INDEX55     0x0080000000000000L");
			WriteLine("#define NULL_MAP_INDEX56     0x0100000000000000L");
			WriteLine("#define NULL_MAP_INDEX57     0x0200000000000000L");
			WriteLine("#define NULL_MAP_INDEX58     0x0400000000000000L");
			WriteLine("#define NULL_MAP_INDEX59     0x0800000000000000L");
			WriteLine("#define NULL_MAP_INDEX60     0x1000000000000000L");
			WriteLine("#define NULL_MAP_INDEX61     0x2000000000000000L");
			WriteLine("#define NULL_MAP_INDEX62     0x4000000000000000L");
			WriteLine("#define NULL_MAP_INDEX63     0x8000000000000000L");
		}

		void GenerateMethodsPointerDeclarationCode() {
			ClearRegion(Commom_Decode_Method_Pointer_Definition_GeneratedCode);
			SetPosition(Commom_Decode_Method_Pointer_Definition_GeneratedCode);
			WriteLine("typedef void* (FastProtocolManager::*FastDecodeMethodPointer)();");
			WriteLine("typedef void* (FastProtocolManager::*FastReleaseMethodPointer)();");
		}

		void Generate_ASTS() {
			XmlDocument doc = new XmlDocument();
			doc.Load(AstsTemplateFile);

			TemplatesNode = GetTemplatesNode(doc);
			if(TemplatesNode == null)
				throw new ArgumentException("Cannot find 'templates' node in asts templates file");

			PrepareForAsts();
			GenerateTemplatesCodeAsts();
			GenerateAddChannelsCode_ASTS();
		}

		void PrepareForAsts() { 
			Prefix = "Fast";
			Mode = GeneratorMode.Asts;
			Decode_Method_Pointer_Definition_GeneratedCode = "Asts_Decode_Method_Pointer_Definition_GeneratedCode";
			Message_Info_Structures_Definition_GeneratedCode = "Asts_Message_Info_Structures_Definition_GeneratedCode";

			SnapshotInfoFields = new List<SnapshotFieldInfo>();
			SnapshotInfoFields.Add(new SnapshotFieldInfo("", "RptSeq"));
			SnapshotInfoFields.Add(new SnapshotFieldInfo("", "LastFragment"));
			SnapshotInfoFields.Add(new SnapshotFieldInfo("", "RouteFirst"));
			SnapshotInfoFields.Add(new SnapshotFieldInfo("", "LastMsgSeqNumProcessed"));
			SnapshotInfoFields.Add(new SnapshotFieldInfo("", "SendingTime"));
			SnapshotInfoFields.Add(new SnapshotFieldInfo("", "Symbol"));
			SnapshotInfoFields.Add(new SnapshotFieldInfo("", "TradingSessionID"));
		}

		void PrepareForSpectra() {
			Prefix = "Spectra";
			Mode = GeneratorMode.Spectra;
			Decode_Method_Pointer_Definition_GeneratedCode = "Spectra_Decode_Method_Pointer_Definition_GeneratedCode";
			Message_Info_Structures_Definition_GeneratedCode = "Spectra_Message_Info_Structures_Definition_GeneratedCode";

			SnapshotInfoFields = new List<SnapshotFieldInfo>();
			SnapshotInfoFields.Add(new SnapshotFieldInfo("", "RptSeq"));
			SnapshotInfoFields.Add(new SnapshotFieldInfo("", "LastFragment"));
			SnapshotInfoFields.Add(new SnapshotFieldInfo("", "RouteFirst"));
			SnapshotInfoFields.Add(new SnapshotFieldInfo("", "LastMsgSeqNumProcessed"));
			SnapshotInfoFields.Add(new SnapshotFieldInfo("", "SendingTime"));
			SnapshotInfoFields.Add(new SnapshotFieldInfo("", "Symbol"));
			SnapshotInfoFields.Add(new SnapshotFieldInfo("", "TradingSessionID"));
		}

		void Generate_Spectra() {
			XmlDocument doc = new XmlDocument();
			doc.Load(SpectraTemplateFile);

			TemplatesNode = GetTemplatesNode(doc);
			if(TemplatesNode == null)
				throw new ArgumentException("Cannot find 'templates' node in spectra templates file");

			PrepareForSpectra();
			GenerateTemplatesCodeSpectra();
			//GenerateAddChannelsCode_ASTS();
		}

		void CheckSaveGeneratedFiles() {
			if(!ManagerHFile.Modified)
				Console.WriteLine(ManagerSourceFileH + " - no changes were made. skip update source file.");
			else
				ManagerHFile.Save();
			if(!ManagerCppFile.Modified)
				Console.WriteLine(ManagerSourceFileCpp + " - no changes were made. skip update source file.");
			else
				ManagerCppFile.Save();
			if(!TypesFile.Modified)
				Console.WriteLine(SourceTypes + " - no changes were made. skip update source file.");
			else
				TypesFile.Save();
			if(!RobotCppFile.Modified)
				Console.WriteLine(RobotCppFile + " - no changes were made. skip update source file.");
			else
				RobotCppFile.Save();
		}

		string Message_Info_Structures_Definition_GeneratedCode = "Message_Info_Structures_Definition_GeneratedCode";
		string Structure_Objects_Declaration_GeneratedCode = "Structure_Objects_Declaration_GeneratedCode";
		string Commom_Decode_Method_Pointer_Definition_GeneratedCode = "Decode_Method_Pointer_Definition_GeneratedCode";
		string Decode_Method_Pointer_Definition_GeneratedCode = "Asts_Decode_Method_Pointer_Definition_GeneratedCode";
		string Decode_Method_Pointer_Arrays_GeneratedCode = "Decode_Method_Pointer_Arrays_GeneratedCode";
		string Decode_Methods_Definition_GeneratedCode = "Decode_Methods_Definition_GeneratedCode";
		string Get_Free_Item_Methods_GeneratedCode = "Get_Free_Item_Methods_GeneratedCode";
		string Encode_Methods_Definition_GeneratedCode = "Encode_Methods_Definition_GeneratedCode";
		string Encode_Methods_Declaration_GeneratedCode = "Encode_Methods_Declaration_GeneratedCode";
		string String_Constant_Declaration_GeneratedCode = "String_Constant_Declaration_GeneratedCode";
		string Print_Methods_Definition_GeneratedCode = "Print_Methods_Definition_GeneratedCode";
		string Print_Methods_Declaration_GeneratedCode = "Print_Methods_Declaration_GeneratedCode";
		string AddDefaultChannels_GeneratedCode = "AddDefaultChannels_GeneratedCode";

		private  void ClearPreviouseGeneratedCode () {
			string[] keywords = new string[] { 
				Message_Info_Structures_Definition_GeneratedCode,
				Structure_Objects_Declaration_GeneratedCode,
				Decode_Method_Pointer_Arrays_GeneratedCode,
				Get_Free_Item_Methods_GeneratedCode,
				Decode_Methods_Definition_GeneratedCode,
				Encode_Methods_Definition_GeneratedCode,
				Encode_Methods_Declaration_GeneratedCode,
				String_Constant_Declaration_GeneratedCode,
				Print_Methods_Declaration_GeneratedCode,
				Print_Methods_Definition_GeneratedCode,
				AddDefaultChannels_GeneratedCode
			};
			foreach(string keyword in keywords) {
				ClearRegion(keyword);
			}
		}

		private void ClearRegion(string keyword) {
			SetPosition(keyword);
			int startingIndex = CurrentFile.Line;
			int endIndex = GetEndRegionLineIndex(startingIndex);
			int count = endIndex - startingIndex;
			for(int i = 0; i < count; i++) {
				CurrentFile.Remove(startingIndex);
			}
		}

		private  int GetEndRegionLineIndex (int startIndex) { 
			int index = startIndex;
			for(int i = startIndex; i < Strings.Count; i++) {
				if(Strings[i].Contains("#pragma") && Strings[i].Contains("endregion"))
					return index;
				index++;
			}
			return Strings.Count;
		}

		private  int GetKeywordLineIndex (string keyword) {
			if(SetPosition(keyword))
				return CurrentFile.Line;
			return -1;
		}

		List<ConstantStringInfo> ConstantStrings { get; set; }

		private void WriteDecodeMethodPointersDefinitionCode() {
			ClearRegion(Decode_Method_Pointer_Definition_GeneratedCode);
			SetPosition(Decode_Method_Pointer_Definition_GeneratedCode);
			WriteLine("typedef " + Prefix + "SnapshotInfo* (FastProtocolManager::*" + Prefix + "GetSnapshotInfoMethodPointer)();");	
		}

		private  void GenerateTemplatesCodeAsts () {
			Console.WriteLine("generate asts...");
			WriteDecodeMethodPointersDefinitionCode();
			WriteEntireMethodAddressArrays(TemplatesNode);
			WriteStructuresDefinitionCode(TemplatesNode, true);
			WriteStructuresDeclarationCode(TemplatesNode);
			ConstantStrings = GetConstantStrings(TemplatesNode);
			WriteStringConstantDeclarationCode(TemplatesNode);
			WriteGetFreeItemCode(TemplatesNode);
			WriteReleaseItemCode(TemplatesNode);

			WriteEncodeMethodsCode(TemplatesNode);
			WriteHeaderParsingCode(TemplatesNode);
			WriteGetTotNumReportsMethod(TemplatesNode);
			WriteDecodeMethodsCode(TemplatesNode);
			WritePrintMethodsCode(TemplatesNode);
			Console.WriteLine("done.");
		}

		private  void GenerateTemplatesCodeSpectra () {
			Console.WriteLine("generate spectra...");
			//WriteDecodeMethodPointersDefinitionCode();

			//WriteEntireMethodAddressArrays(TemplatesNode);
			//WriteStructuresDefinitionCode(TemplatesNode, false);
			//WriteStructuresDeclarationCode(TemplatesNode);
			//ConstantStrings = GetConstantStrings(TemplatesNode);
			//WriteStringConstantDeclarationCode(TemplatesNode);
			//WriteGetFreeItemCode(TemplatesNode);
			//WriteReleaseItemCode(TemplatesNode);

			//WriteEncodeMethodsCode(TemplatesNode);
			//WriteHeaderParsingCode(TemplatesNode);
			//WriteGetTotNumReportsMethod(TemplatesNode);
			//WriteDecodeMethodsCode(TemplatesNode);
			//WritePrintMethodsCode(TemplatesNode);

			Console.WriteLine("done.");
		}

		class ConstantStringInfo {
			public XmlNode Node { get; set; }
			public string Name { get { return Node.Attributes["name"].Value; } }
			public string Value { get { return Node.ChildNodes[0].Attributes["value"].Value; } }
			public string FieldName { get { return Name + "ConstString"; } }
		}

		private bool HasConstString(XmlNode node) {
			return node.Name == "string" && node.ChildNodes.Count == 1 && (node.ChildNodes[0].Name == "default"/* || node.ChildNodes[0].Name == "constant"*/);
		}

		private List<ConstantStringInfo> GetConstantStrings(XmlNode node) {
			List<ConstantStringInfo> res = new List<ConstantStringInfo>();
			GetConstantStrings(node, res);
			return res;
		}

		private void GetConstantStrings(XmlNode node, List<ConstantStringInfo> list) {
			foreach(XmlNode child in node.ChildNodes) {
				if(HasConstString(child))
					list.Add(new ConstantStringInfo() { Node = child });
				GetConstantStrings(child, list);
			}
		}

		private void WriteStringConstantDeclarationCode(XmlNode node) {
			SetPosition(String_Constant_Declaration_GeneratedCode);
			WriteLine("public:");
			foreach(ConstantStringInfo info in ConstantStrings) {
				WriteLine("\tchar\t" + info.FieldName + "[" + (info.Value.Length + 1) + "];");
				WriteLine("\tconst UINT\t" + info.FieldName + "Length = " + info.Value.Length + ";");
			}
			WriteLine("private:");
			WriteLine("");
			WriteLine("\tvoid InitializeConstantStrings() {");
			foreach(ConstantStringInfo info in ConstantStrings) {
				WriteLine("\t\tsprintf(" + info.FieldName + ", \"" + info.Value + "\");");
			}
			WriteLine("\t}");
		}

		private  void WriteEncodeMethodsCode (XmlNode templatesNode) {
			List<StructureInfo> st = GetStructures(TemplatesNode);
			SetPosition(Encode_Methods_Declaration_GeneratedCode);
			foreach(StructureInfo info in st) {
				if(info.IsSequence)
					continue;
				WriteEncodeMethodDeclarationMethodCode(info);
			}
			SetPosition(Encode_Methods_Definition_GeneratedCode);
			foreach(StructureInfo info in st) {
				if(info.IsSequence)
					continue;
				WriteEncodeMethodCode(info);
			}
		}

		private void WriteEncodeMethodDeclarationMethodCode (StructureInfo info) {
			WriteLine("\tvoid " + info.EncodeMethodName + "(" + info.Name + "* info);");
		}

		private void WriteEncodeMethodCode (StructureInfo info) {
			WriteLine("void FastProtocolManager::" + info.EncodeMethodName + "(" + info.Name + "* info) {");
			WriteLine("\tWritePresenceMap(info->PresenceMap); // Presence Map hack");
			WriteLine("\tWriteUInt32_Mandatory(" + info.Node.Attributes["id"].Value + ");");
			int presenceByteCount = CalcPresenceMapByteCount(info.Node);
			if(GetMaxPresenceBitCount(info.Node) > 0)
				WriteLine("\tWritePresenceMap" + presenceByteCount + "(info->PresenceMap);");
			foreach(XmlNode node in info.Node.ChildNodes) {
				info.Parent = null;
				WriteEncodeValueCode(node, info, "\t");
			}
			WriteLine("}");
		}

		private void WriteNullValueCode(string tabs, XmlNode value) {
			if(value.Name == "string")
				WriteLine(tabs + "this->WriteNullString();");
			else 
				WriteLine(tabs + "this->WriteNull();");
		}

		private  void WriteEncodeValueCode (XmlNode field, StructureInfo si, string tabs) {
			bool nullCheck = ShouldWriteNullCheckCode(field);
			bool presenceCheck = ShouldWriteCheckPresenceMapCode(field);
			if(!CanParseValue(field))
				return;
			if(presenceCheck) {
				string bracket = nullCheck ? " {" : "";
				string checkPresenceMethodName = HasOptionalPresence(field)? "CheckOptionalFieldPresence": "CheckMandatoryFieldPresence";
				WriteLine(tabs + "if(" + checkPresenceMethodName + "(" + si.InCodeValueName + "->PresenceMap, PRESENCE_MAP_INDEX" + CalcFieldPresenceIndex(field) + "))" + bracket);

				tabs += "\t";
			}
			if(nullCheck) {
				int nullIndex = CalcNullIndex(field);
				WriteLine(tabs + "if((" + si.InCodeValueName + "->NullMap & NULL_MAP_INDEX" + nullIndex + ") != 0)");
				WriteNullValueCode(tabs + "\t", field);

				if(field.Name == "sequence")
					WriteLine(tabs + "else {");
				else 
					WriteLine(tabs + "else");

				tabs += "\t";
			}
			if(field.Name == "string")
				WriteStringEncodeMethodCode(field, si, tabs);
			else if(field.Name == "uInt32")
				WriteUint32EncodeMethodCode(field, si, tabs);
			else if(field.Name == "int32")
				WriteInt32EncodeMethodCode(field, si, tabs);
			else if(field.Name == "uInt64")
				WriteUint64EncodeMethodCode(field, si, tabs);
			else if(field.Name == "int64")
				WriteInt64EncodeMethodCode(field, si, tabs);
			else if(field.Name == "decimal")
				WriteDecimalEncodeMethodCode(field, si, tabs);
			else if(field.Name == "byteVector")
				WriteByteVectorEncodeMethodCode(field, si, tabs);
			else if(field.Name == "sequence") {
				WriteSequenceEncodeMethodCode(field, si, tabs);
				if(nullCheck) {
					tabs = tabs.Substring(1);
					WriteLine(tabs + "}");
				}

			} else if(field.Name == "length") {
				// Do nothing
			}
			if(nullCheck && presenceCheck) {
				tabs = tabs.Substring(1);
				WriteLine(tabs + "}");
			}
			if(presenceCheck) {
				tabs = tabs.Substring(1);
			}
		}

		private  void WriteSequenceEncodeMethodCode (XmlNode field, StructureInfo si, string tabs) {
			string itemInfo = GetIemInfoPrefix(field) + "ItemInfo";
			StructureInfo info = new StructureInfo() { InCodeValueName = "(*" + itemInfo + ")", NameCore = si.NameCore + ItemName(field), IsSequence = true };
			StructureInfo item = GetOriginalStruct(field);
			if(item == null)
				item = info;
			string methodName = HasOptionalPresence(field)? "WriteUInt32_Optional": "WriteUInt32_Mandatory";
			WriteLine(tabs + methodName + "(" + si.InCodeValueName + "->" + Name(field) + "Count);");
			WriteLine(tabs + item.Name + " **" + itemInfo + " = " + si.InCodeValueName + "->" + Name(field) + ";");
			WriteLine(tabs + "for(int i = 0; i < " + si.InCodeValueName + "->" + Name(field) + "Count; i++) {");
			if(GetMaxPresenceBitCount(field) > 0) {
				WriteLine(tabs + "\tWritePresenceMap((*" + itemInfo + ")->PresenceMap); // Presence Map hack");
				WriteLine("");
			}
			foreach(XmlNode node in field.ChildNodes) {
				WriteEncodeValueCode(node, info, tabs + "\t");
			}
			WriteLine(tabs + "\t" + itemInfo + "++;");
			WriteLine(tabs + "}");
		}

		private  void WriteByteVectorEncodeMethodCode (XmlNode field, StructureInfo si, string tabs) {
			string methodName = HasOptionalPresence(field)? "WriteByteVector_Optional": "WriteByteVector_Mandatory";
			WriteLine(tabs + methodName + "(" + si.InCodeValueName + "->" + Name(field) + ", " + si.InCodeValueName + "->" + Name(field) + "Length);");
		}

		private  void WriteDecimalEncodeMethodCode (XmlNode field, StructureInfo si, string tabs) {
			string methodName = HasOptionalPresence(field) ? "WriteDecimal_Optional" : "WriteDecimal_Mandatory";
			WriteLine(tabs + methodName + "(&(" + si.InCodeValueName + "->" + Name(field) + "));");
		}

		private  void WriteInt64EncodeMethodCode (XmlNode field, StructureInfo si, string tabs) {
			string methodName = HasOptionalPresence(field) ? "WriteInt64_Optional" : "WriteInt64_Mandatory";
			WriteLine(tabs + methodName + "(" + si.InCodeValueName + "->" + Name(field) + ");");
		}

		private  void WriteUint64EncodeMethodCode (XmlNode field, StructureInfo si, string tabs) {
			string methodName = HasOptionalPresence(field) ? "WriteUInt64_Optional" : "WriteUInt64_Mandatory";
			WriteLine(tabs + methodName + "(" + si.InCodeValueName + "->" + Name(field) + ");");
		}

		private  void WriteInt32EncodeMethodCode (XmlNode field, StructureInfo si, string tabs) {
			string methodName = HasOptionalPresence(field) ? "WriteInt32_Optional" : "WriteInt32_Mandatory";
			WriteLine(tabs + methodName + "(" + si.InCodeValueName + "->" + Name(field) + ");");
		}

		private  void WriteUint32EncodeMethodCode (XmlNode field, StructureInfo si, string tabs) {
			string methodName = HasOptionalPresence(field) ? "WriteUInt32_Optional" : "WriteUInt32_Mandatory";
			WriteLine(tabs + methodName + "(" + si.InCodeValueName + "->" + Name(field) + ");");
		}

		private  void WriteStringEncodeMethodCode (XmlNode field, StructureInfo si, string tabs) {
			string methodName = HasOptionalPresence(field) ? "WriteString_Optional" : "WriteString_Mandatory";
			if(HasConstantAttribute(field))
				WriteLine(tabs + methodName + "(\"" + GetFieldConstantValue(field) + "\", " + GetFieldConstantValue(field).Length + ");");
			else 
				WriteLine(tabs + methodName + "(" + si.InCodeValueName + "->" + Name(field) + ", " + si.InCodeValueName + "->" + Name(field) + "Length);");
		}

		private  List<XmlNode> GetAllMessages (XmlNode templatesNode) {
			List<XmlNode> res = new List<XmlNode>();
			foreach(XmlNode node in templatesNode.ChildNodes) {
				if(node.Name == "template")
					res.Add(node);
			}
			return res;
		}

		private  void WriteGetFreeItemCode (XmlNode templatesNode) {
			SetPosition(Get_Free_Item_Methods_GeneratedCode);

			WriteLine("public:");
			foreach(StructureInfo str in Structures) {
				WriteLine("\tinline " + str.Name + "* " + str.GetFreeMethodName + "() {");
				WriteLine("\t\treturn this->" + str.ValueName + "->NewItem();");
				WriteLine("\t}");
				WriteLine("");
				WriteLine("\tinline AutoAllocatePointerList<" + str.Name + ">* " + str.GetListMethodName + "() {");
				WriteLine("\t\treturn this->" + str.ValueName + ";");
				WriteLine("\t}");
				WriteLine("");
			}
			WriteLine("private:");
		}

		public string NameWithParent(XmlNode node) {
			string name = string.Empty;
			while(node.Name != "templates") {
				if(node.Name == "template")
					name = GetTemplateName(node.PreviousSibling.Value) + name;
				else 
					name = ItemName(node) + name;
				node = node.ParentNode;
			}
			return name;
		}

		private void WriteReleaseItemCode (XmlNode templatesNode) {
			foreach(StructureInfo str in Structures) {
				WriteLine("\tvoid " + str.ReleaseMethodName + "() {");
				WriteLine("\t\t((" + str.Name + "*)this->LastDecodeInfo())->ReleaseUnused();");
				WriteLine("\t}");
			}
			int minId = CalcMinTemplateId(templatesNode);
			WriteLine("\tinline void Reset() {");
			WriteLine("\t\tFastReleaseMethodPointer funcPtr = this->ReleaseMethods[this->m_templateId - " + minId + "];");
			WriteLine("\t\t(this->*funcPtr)();");
			WriteLine("\t}");
		}

		public class StructureInfo {
			public StructureInfo() { 
				Prefix = "Fast";
			}
			public string Prefix { get; set; }
			public string Name {
				get {
					return Prefix + NameCore + Suffix;
				}
			}

			public string PresenceIndicesClassName { 
				get { return Name + "PresenceIndices"; }
			}

			public string NullIndicesClassName { 
				get{ return Name + "NullIndices"; }
			}

			public XmlNode Node { get; set; }

			public string NameCore { get; set; }

			public bool IsSequence { get; set; }

			public string ValueName { 
				get { 
					return "m_" + NameCore.Substring(0, 1).ToLower() + NameCore.Substring(1) + (IsSequence ? "Items" : ""); 
				} 
			}

			public string PrevValueName {
				get {
					return "m_prev" + NameCore + (IsSequence ? "Item" : "") + "Info"; 
				}
			}

			public string CurrentItemValueName {
				get {
					return ValueName + "CurrentItem";
				}
			}

			public string MaxItemCountValueName {
				get { return ValueName + "MaxCount"; }
			}

			public string Suffix {
				get { return IsSequence ? "ItemInfo" : "Info"; }
			}

			public string GetFreeMethodName {
				get { return "GetFree" + NameCore + Suffix; }
			}

			public string GetListMethodName { 
				get{ return "Get" + NameCore + Suffix + "Pool"; }
			}

			public string AllocatePoolMethodName { 
				get{ return "Allocate" + NameCore + Suffix + "Pool"; }
			}

			public string ReleaseMethodName { 
				get { return "Release" + NameCore + Suffix; }
			}

			public string EncodeMethodName {
				get { return "Encode" + NameCore + Suffix; }
			}

			public StructureInfo Parent { get; set; }
			List<StructureInfo> incStruct;
			public List<StructureInfo> IncrementalStructures { 
				get { 
					if(incStruct == null)
						incStruct = new List<StructureInfo>();
					return incStruct;
				}
			}
			public bool HasIncrementalStruct(XmlNode node) {
				if(IncrementalStructures.Count == 0)
					return false;
				XmlNode parentNode = node.ParentNode;
				if(parentNode == null || parentNode.Attributes["name"] == null)
					return false;
				//Console.WriteLine("Seeking inc " + parentNode.Attributes["name"].Value);
				foreach(StructureInfo info in IncrementalStructures) {
					XmlNode pn = info.Node.ParentNode;
					//if(pn == null)
					//	Console.WriteLine("pn == null");
					//Console.WriteLine("Check " + pn.Attributes["name"].Value);
					if(pn == parentNode) {
						//Console.WriteLine("found.");
						return true;
					}
				}
				//Console.WriteLine("not found");
				return false;
			}
			public string InStructFieldName { get; set; }
			string inCodeValueName = "info";
			public string InCodeValueName { 
				get { 
					if(Parent == null)
						return inCodeValueName;
					return Parent.InCodeValueName + "->" + InStructFieldName;
				}
				set { 
					inCodeValueName = value;
				}
			}
			public List<XmlNode> Fields { get; set; }
		}

		private  List<StructureInfo> GetStructures (XmlNode templatesNode) {
			List<StructureInfo> res = new List<StructureInfo>();
			foreach(XmlNode node in templatesNode.ChildNodes) {
				if(node.Name == "template") {
					string nameCore = GetTemplateName(node.PreviousSibling.Value);
					List<StructureInfo> child = new List<StructureInfo>();
					GetSequenceStructureNames(nameCore, node, child);
					StructureInfo info = new StructureInfo() { NameCore = nameCore, Node = node };
					foreach(StructureInfo c in child) {
						res.Add(c);
						c.Parent = info;
					}
					info.Fields = new List<XmlNode>();
					foreach(XmlNode field in node.ChildNodes) {
						info.Fields.Add(field);
					}
					res.Add(info);
				}
			}
			return res;
		}

		private  void GetSequenceStructureNames (string parentStructNameCore, XmlNode parent, List<StructureInfo> res) {
			foreach(XmlNode node in parent.ChildNodes) {
				if(node.Name != "sequence")
					continue;
				string nameCore = parentStructNameCore + ItemName(node);
				List<StructureInfo> child = new List<StructureInfo>();
				GetSequenceStructureNames(nameCore, node, child);
				StructureInfo info = new StructureInfo() { IsSequence = true, NameCore = nameCore, Node = node }; 
				foreach(StructureInfo c in child) {
					res.Add(c);
					c.Parent = info;
				}
				info.Fields = new List<XmlNode>();
				foreach(XmlNode field in node.ChildNodes) {
					info.Fields.Add(field);
				}
				res.Add(info);
			}
		}

		private  void WriteStructuresDeclarationCode (XmlNode templatesNode) {
			SetPosition(Structure_Objects_Declaration_GeneratedCode);

			foreach(StructureInfo str in Structures) {
				WriteLine("\tAutoAllocatePointerList<" + str.Name + ">\t*" + str.ValueName + ";");
			}
			foreach(StructureInfo str in Structures) {
				WriteLine("\t" + str.Name + "\t*" + str.PrevValueName + ";");
			}

			WriteLine("");
			WriteLine("\tvoid InitializeMessageInfo() {");
			foreach(StructureInfo str in structures) {
				WriteLine("\t\tthis->" + str.ValueName + " = this->m_allocationInfo->" + str.GetListMethodName + "();");
			}
			foreach(StructureInfo str in structures) {
				WriteLine("\t\tthis->" + str.PrevValueName + " = this->" + str.GetFreeMethodName + "();");
				WriteLine("\t\tthis->" + str.PrevValueName + "->Used = true;");
			}
			WriteLine("\t}");

			WriteLine("");
		}

		private List<XmlNode> GetTemplates(XmlNode templatesNode) {
			List<XmlNode> res = new List<XmlNode>();

			foreach(XmlNode node in templatesNode.ChildNodes) {
				if(node.Name == "template")
					res.Add(node);
			}
			return res;
		}

		private List<string> CollectHeaderTags(XmlNode templatesNode) {
			List<string> headerTags = new List<string>();
			List<XmlNode> templates = GetTemplates(templatesNode);
			 
			for(int i = 0; i < templates[0].ChildNodes.Count; i++) {
				string tagId = templates[0].ChildNodes[i].Attributes["id"].Value;
				//Console.WriteLine("checking " + tagId);
				for(int j = 1; j < templates.Count; j++) {
					if(i >= templates[j].ChildNodes.Count)
						return headerTags;
					string tagId2 = templates[j].ChildNodes[i].Attributes["id"].Value;
					if(tagId != tagId2) {
						//Console.WriteLine("non header tag expected " + tagId + " but found " + tagId2);
						return headerTags;
					}
				}
				//Console.WriteLine("add header tag " + templates[0].ChildNodes[i].Attributes["name"].Value);
				headerTags.Add(templates[0].ChildNodes[i].Attributes["id"].Value);
			}
			return headerTags;
		}

		protected List<string> HeaderTags { get; set; }
		private void WriteHeaderParsingCode(XmlNode templatesNode) {
			SetPosition(Decode_Methods_Definition_GeneratedCode);

			WriteLine("\tinline void DecodeHeader() {"); 
			WriteLine("");
			WriteLine("\t\tthis->ParsePresenceMap(&(this->m_presenceMap));");
			WriteLine("\t\tthis->m_templateId = ReadUInt32_Mandatory();");
			WriteLine("\t}");
			WriteLine("");
		}

		private  void WriteDecodeMethodsCode (XmlNode templatesNode) {
			foreach(XmlNode node in templatesNode.ChildNodes) {
				if(node.Name != "template")
					continue;
				ParseTemplateNode(node, GetTemplateName(node.PreviousSibling.Value));
			}
			foreach(XmlNode node in templatesNode.ChildNodes) {
				if(node.Name != "template")
					continue;
				WriteGetSnapshotInfoMethod(node, GetTemplateName(node.PreviousSibling.Value));
			}
			WriteEntireMethodsCode(templatesNode);
		}

		private void WritePrintMethodsCode(XmlNode templatesNode) {
			SetPosition(Print_Methods_Declaration_GeneratedCode);
			foreach(XmlNode node in templatesNode.ChildNodes) {
				if(node.Name == "template") {
					PrintDeclareTemplateNode(node, GetTemplateName(node.PreviousSibling.Value));
				}
			}
			foreach(XmlNode node in templatesNode.ChildNodes) {
				if(node.Name == "template") {
					PrintXmlDeclareTemplateNode(node, GetTemplateName(node.PreviousSibling.Value));
				}
			}

			SetPosition(Print_Methods_Definition_GeneratedCode);
			foreach(XmlNode node in templatesNode.ChildNodes) {
				if(node.Name == "template") {
					PrintTemplateNode(node, GetTemplateName(node.PreviousSibling.Value));
				}
			}
			foreach(XmlNode node in templatesNode.ChildNodes) {
				if(node.Name == "template") {
					PrintXmlTemplateNode(node, GetTemplateName(node.PreviousSibling.Value));
				}
			}
		}

		Dictionary<string, string> similarTemplates;
		protected Dictionary<string, string> TemplatesMap { 
			get { 
				if(similarTemplates == null) {
					similarTemplates = new Dictionary<string, string>();
					similarTemplates.Add("X-Generic", "W-Generic");

					similarTemplates.Add("X-OLR-FOND", "W-OLS-FOND");
					similarTemplates.Add("X-TLR-FOND", "W-TLS-FOND");
					similarTemplates.Add("X-OBR-FOND", "W-OBS-FOND");
					similarTemplates.Add("X-MSR-FOND", "W-Generic");

					similarTemplates.Add("X-OLR-CURR", "W-OLS-CURR");
					similarTemplates.Add("X-TLR-CURR", "W-TLS-CURR");
					similarTemplates.Add("X-OBR-CURR", "W-OBS-CURR");
					similarTemplates.Add("X-MSR-CURR", "W-Generic");
				}
				return similarTemplates;
			}
		}

		StructureInfo FindIncrementalStructForTemplate(List<StructureInfo> str, StructureInfo snap){
			XmlNode snapeParentNode = snap.Node.ParentNode;
			if(snapeParentNode.Name != "template")
				return null;
			string snapParentName = snapeParentNode.Attributes["name"].Value;

			//Console.WriteLine("Seek similar for " + infoParentName);
			foreach(StructureInfo incInfo in str) { 
				XmlNode incParentNode = incInfo.Node.ParentNode;
				if(incParentNode.Name != "template")
					continue;
				string incParentName = incParentNode.Attributes["name"].Value;
				//Console.WriteLine("checking " + infoParentName2);

				string nameToCheck = string.Empty;
				if(!TemplatesMap.TryGetValue(incParentName, out nameToCheck))
					continue;
				if(nameToCheck != snapParentName)
					continue;
				if(snap.HasIncrementalStruct(incInfo.Node))
					continue;
				return incInfo;
			}
			
			return null;
		}

		List<StructureInfo> MergeStructures(List<StructureInfo> str) {
			List<StructureInfo> res = new List<StructureInfo>();
			List<StructureInfo> strToRemove = new List<StructureInfo>();
			foreach(StructureInfo info in str) {
				if(!info.IsSequence) {
					res.Add(info);
					continue;
				}

				while(true) {
					StructureInfo info2 = FindIncrementalStructForTemplate(str, info);
					if(info2 == null) {
						res.Add(info);
						break;
					}
					//Console.WriteLine("Found Incrementsal Structure for " + info.Name + " -> " + info2.Name);
					strToRemove.Add(info2);
					if(info.IncrementalStructures.Contains(info2)) {
						throw new Exception("Structure found twice");
					}
					info.IncrementalStructures.Add(info2);
				
					foreach(XmlNode node2 in info2.Fields) {
						bool foundField = false;
						foreach(XmlNode node in info.Fields) {
							if(Name(node) == Name(node2)) {
								foundField = true;
								break;
							}
						}
						if(!foundField)
							info.Fields.Add(node2);
					}
				}
			}
			foreach(StructureInfo info in strToRemove) {
				res.Remove(info);
			}
			return res;
		}

		private void WriteSnapshotInfoDefinitionCode(XmlNode templatesNode) {
			WriteLine("class " + Prefix + "SnapshotInfo {");
			WriteLine("public:");
			WriteLine("\tUINT64\t\t\t\tPresenceMap;");
			WriteLine("\tUINT64\t\t\t\tNullMap;");
			WriteLine("\tint\t\t\t\tTemplateId;");
			InitializeSnapshotInfoFields(templatesNode);
			foreach(SnapshotFieldInfo info in SnapshotInfoFields) {
				if(info.FieldType.ToLower() == "string" ) {
					WriteLine("\t" + "char" + "\t\t\t\t" + info.FieldName + "[32];");
					WriteLine("\t" + "int" + "\t\t\t\t\t" + info.FieldName + "Length;");
				} else {
					WriteLine("\t" + info.FieldType + "\t\t\t\t" + info.FieldName + ";");
				}
			}
			WriteLine("\t" + Prefix + "SnapshotInfo() {");
			WriteLine("\t\tthis->PresenceMap = 0;");
			WriteLine("\t\tthis->NullMap = 0;");
			WriteLine("\t}");
			WriteLine("};");

			WriteLine("");
		}

		private void WriteObjectsAllocationInfo() {
			WriteLine("class " + Prefix + "ObjectsAllocationInfo {");
			foreach(StructureInfo info in Structures) {
				WriteLine("\tAutoAllocatePointerList<" + info.Name + ">" + "\t\t\t\t*" + info.ValueName + ";");
			}
			WriteLine("public:");
			WriteLine("\t static " + Prefix + "ObjectsAllocationInfo *Default;");
			WriteLine("\t" + Prefix + "ObjectsAllocationInfo(int count) {");
			foreach(StructureInfo info in Structures) {
				WriteLine("\t\tthis->" + info.ValueName + " = new AutoAllocatePointerList<" + info.Name + ">(count, count, \"" + info.Name + "\");");
			}
			WriteLine("\t}");
			foreach(StructureInfo info in Structures) {
				WriteLine("\tinline void " + info.AllocatePoolMethodName + "(int count, int addCount) {");
				WriteLine("\t\tthis->" + info.ValueName + "->Append(count);");
				WriteLine("\t\tthis->" + info.ValueName + "->AddCount(addCount);");
				WriteLine("\t}");
			}
			foreach(StructureInfo info in Structures) {
				WriteLine("\tinline void " + info.AllocatePoolMethodName + "To(int count) {");
				WriteLine("count -= this->" + info.ValueName + "->Capacity();");
				WriteLine("if(count > 0)");
				WriteLine("\t\t\tthis->" + info.ValueName + "->Append(count);");
				WriteLine("\t}");
			}
			foreach(StructureInfo info in Structures) {
				WriteLine("\tinline AutoAllocatePointerList<" + info.Name + ">* " + info.GetListMethodName + "() {");
				WriteLine("\t\treturn this->" + info.ValueName + ";");
				WriteLine("\t}");
			}
			WriteLine("};");
		}

		private void WritePresenceIndexClasses(List<StructureInfo> structures) {
			foreach(StructureInfo info in structures) {
				bool hasPresenceIndex = false;
				foreach(XmlNode field in info.Fields) {
					if(!ShouldWriteCheckPresenceMapCode(field))
						continue;
					hasPresenceIndex = true;
					break;
				}
				if(!hasPresenceIndex)
					continue;
				WriteLine("class " + info.PresenceIndicesClassName + "{");
				WriteLine("public:");
				foreach(XmlNode field in info.Fields) {
					if(!ShouldWriteCheckPresenceMapCode(field))
						continue;
					WriteLine("\tstatic const UINT64 " + Name(field) + "PresenceIndex = PRESENCE_MAP_INDEX" + CalcFieldPresenceIndex(field) + ";");
				}
				WriteLine("};");
			}
		}

		private void WriteNullIndexClasses(List<StructureInfo> structures) {
			foreach(StructureInfo info in structures) {
				bool hasNullableIndex = false;
				foreach(XmlNode field in info.Fields) {
					if(!ShouldWriteNullCheckCode(field))
						continue;
					hasNullableIndex = true;
					break;
				}
				if(!hasNullableIndex)
					continue;
				WriteLine("class " + info.NullIndicesClassName + "{");
				WriteLine("public:");
				foreach(XmlNode field in info.Fields) {
					if(!ShouldWriteNullCheckCode(field))
						continue;
					WriteLine("\tstatic const UINT64 " + Name(field) + "NullIndex = NULL_MAP_INDEX" + CalcNullIndex(field) + ";");
				}
				WriteLine("};");
			}
		}

		private  void WriteStructuresDefinitionCode (XmlNode templatesNode, bool writeSnapshotInfoCode) {
			SetPosition(Message_Info_Structures_Definition_GeneratedCode);
			if(writeSnapshotInfoCode)
				WriteSnapshotInfoDefinitionCode(templatesNode);

			foreach(StructureInfo info in Structures) { 
				WriteStructureDefinition(info);
			}

			List<StructureInfo> structures = GetStructures(templatesNode);
			WriteObjectsAllocationInfo();
			WritePresenceIndexClasses(structures);
			WriteNullIndexClasses(structures);
		}

		int GetMaxSize(XmlNode field) {
			return HasAttribute(field, "size") ? int.Parse(field.Attributes["size"].Value) : 0;
		}

		int GetMaxStringSize(XmlNode field) {
			int maxStringLength = GetMaxSize(field);
			if(maxStringLength == 0) {
				maxStringLength = 16;
				string name = Name(field);
				if(name == "Text")
					maxStringLength = 512;
				if(name == "TargetCompID" || name == "SenderCompID")
					maxStringLength = 32;
				if(name == "MDEntryType")
					maxStringLength = 4;
				if(name == "OpenCloseSettlFlag")
					maxStringLength = 4;
				if(name == "OrdType")
					maxStringLength = 4;
				if(name == "SettlType")
					maxStringLength = 4;
				if(name == "OrderSide")
					maxStringLength = 4;
				if(name == "OrderStatus")
					maxStringLength = 4;
				if(name == "CXFlag")
					maxStringLength = 4;
				if(name == "TradingSessionSubID")
					maxStringLength = 4;
			}
			return maxStringLength;
		}

		void WriteStringDefinitionCore(XmlNode field, string tabs) {
			int maxStringLength = GetMaxStringSize(field);
			WriteLine("\tchar" + tabs + Name(field) + "[" + maxStringLength + "];" + GetCommentLine(field));
			WriteLine("\tint"+ tabs + Name(field) + "Length = 0;");
		}

		int GetMaxByteVectorSize(XmlNode field) {
			int maxStringLength = GetMaxSize(field);
			if(maxStringLength == 0) {
				maxStringLength = 128;
				//string name = Name(field);
				/*
				if(name == "Text")
					maxStringLength = 512;
				if(name == "TargetCompID" || name == "SenderCompID")
					maxStringLength = 32;
				if(name == "MDEntryType")
					maxStringLength = 4;
				if(name == "OpenCloseSettlFlag")
					maxStringLength = 4;
				if(name == "OrdType")
					maxStringLength = 4;
				if(name == "SettlType")
					maxStringLength = 4;
				if(name == "OrderSide")
					maxStringLength = 4;
				if(name == "OrderStatus")
					maxStringLength = 4;
				if(name == "CXFlag")
					maxStringLength = 4;
				if(name == "TradingSessionSubID")
					maxStringLength = 4;
				*/
			}
			return maxStringLength;
		}

		void WriteByteVectorDefinitionCore(XmlNode field, string tabs) {
			int maxStringLength = GetMaxByteVectorSize(field);
			WriteLine("\tunsigned char" + tabs + Name(field) + "[" + maxStringLength + "];" + GetCommentLine(field));
			WriteLine("\tint"+ tabs + Name(field) + "Length = 0;");
		}

		List<StructureInfo> structures;
		protected List<StructureInfo> Structures { 
			get { 
				if(structures == null)
					structures = MergeStructures(GetStructures(TemplatesNode));
				return structures;
			}
		}

		int CalcMaxTemplateId(XmlNode templatesNode) {
			List<XmlNode> list = GetTemplates(templatesNode);
			int id = 0;
			foreach(XmlNode t in list) {
				int tid = Int32.Parse(t.Attributes["id"].Value);
				id = Math.Max(id, tid);
			}
			return id;
		}

		int CalcMinTemplateId(XmlNode templatesNode) {
			List<XmlNode> list = GetTemplates(templatesNode);
			int id = 100000;
			foreach(XmlNode t in list) {
				int tid = Int32.Parse(t.Attributes["id"].Value);
				id = Math.Min(id, tid);
			}
			return id;
		}

		private  void WriteEntireMethodAddressArrays (XmlNode templatesNode) {
			SetPosition(Decode_Method_Pointer_Arrays_GeneratedCode);
			WriteLine("\tFastDecodeMethodPointer* DecodeMethods;");
			WriteLine("\tFastReleaseMethodPointer* ReleaseMethods;");
			WriteLine("\tFastGetSnapshotInfoMethodPointer* GetSnapshotInfoMethods;");
			WriteLine("");
			WriteLine("\tvoid InitializeDecodeMethodPointers() {");
			int maxId = CalcMaxTemplateId(templatesNode);
			int minId = CalcMinTemplateId(templatesNode);
			int count = maxId - minId + 1;

			WriteLine("\t\tint ptCount = " + count + ";");
			WriteLine("\t\tthis->DecodeMethods = new FastDecodeMethodPointer[ptCount];");
			WriteLine("\t\tthis->ReleaseMethods = new FastReleaseMethodPointer[ptCount];");
			WriteLine("\t\tthis->GetSnapshotInfoMethods = new FastGetSnapshotInfoMethodPointer[ptCount];");

			WriteLine("");
			WriteLine("\t\tfor(int i = 0; i < " + count + "; i++) {");
			WriteLine("\t\t\tthis->DecodeMethods[i] = &FastProtocolManager::DecodeUnsupportedMessage;");
			WriteLine("\t\t\tthis->GetSnapshotInfoMethods[i] = &FastProtocolManager::GetSnapshotInfoUnsupported;");
			WriteLine("\t\t}");
			WriteLine("");
			List<DecodeMessageInfo> methods = GetDecodeMessageMethods(templatesNode);
			foreach(DecodeMessageInfo info in methods) {
				WriteLine("\t\tthis->DecodeMethods[" + info.TemplateId + " - " + minId + "] = &FastProtocolManager::" + info.FullDecodeMethodName + ";");
			}
			foreach(DecodeMessageInfo info in methods) {
				WriteLine("\t\tthis->ReleaseMethods[" + info.TemplateId + " - " + minId + "] = &FastProtocolManager::" + info.FullDecodeMethodName + ";");
			}
			foreach(DecodeMessageInfo info in methods) {
				if(!info.HasGetSnapshotInfoMethod)
					continue;
				WriteLine("\t\tthis->GetSnapshotInfoMethods[" + info.TemplateId + " - " + minId + "] = &FastProtocolManager::" + info.FullGetSnapshotInfoMethod + ";");
			}
			WriteLine("");
			WriteLine("\t}");
			WriteLine("");
		}

		private  bool SetPosition (string keyword) {
			ManagerHFile.GoTo(0);
			ManagerCppFile.GoTo(0);
			TypesFile.GoTo(0);
			RobotCppFile.GoTo(0);
			int index = ManagerHFile.FindString(keyword);
			if(index >= 0) {
				ManagerHFile.GoTo(index + 1);
				CurrentFile = ManagerHFile;
				return true;
			}
			index = ManagerCppFile.FindString(keyword);
			if(index >= 0) {
				ManagerCppFile.GoTo(index + 1);
				CurrentFile = ManagerCppFile;
				return true;
			}
			index = TypesFile.FindString(keyword);
			if(index >= 0) {
				TypesFile.GoTo(index + 1);
				CurrentFile = TypesFile;
				return true;
			}
			index = RobotCppFile.FindString(keyword);
			if(index >= 0) {
				RobotCppFile.GoTo(index + 1);
				CurrentFile = RobotCppFile;
				return true;
			}

			Console.WriteLine("hfile " + ManagerSourceFileH + " " + ManagerHFile.Lines.Count);
			Console.WriteLine("cppfile " + ManagerSourceFileCpp + " " + ManagerCppFile.Lines.Count);
			Console.WriteLine("types_file " + TypesFile.Lines.Count);
			throw new Exception("error cant find keyword " + keyword);
		}

		class DecodeMessageInfo {
			public DecodeMessageInfo() { 
				Prefix = "Fast";
			}
			public string Prefix { get; set; }
			public string NameCore { get; set; }
			public string MsgType { get; set; }
			public int TemplateId { get; set; }
			public string FullDecodeMethodName { get { return "Decode" + NameCore; } }
			public string FullReleaseMethodName { get { return "Release" + NameCore; } }
			public bool HasGetSnapshotInfoMethod { get; set; } 
			public string FullGetSnapshotInfoMethod { get { return "GetSnapshotInfo" + NameCore; } }
			public string PrintMethodName { get { return "Print" + NameCore; } }
			public string PrintXmlMethodName { get { return "PrintXml" + NameCore; } }
			public string StructName { get { return Prefix + NameCore + "Info"; } }
		}

		private  void WriteEntireMethodsCode (XmlNode templatesNode) {
			int minId = CalcMinTemplateId(templatesNode);
			WriteLine("\tinline void* Decode() {");
			WriteLine("\t\tthis->DecodeHeader();");
			WriteLine("\t\tif(this->ShouldSkipTemplate())");
			WriteLine("\t\t\treturn 0;");
			WriteLine("\t\tFastDecodeMethodPointer funcPtr = this->DecodeMethods[this->m_templateId - " + minId + "];");
			WriteLine("\t\tthis->m_lastDecodedInfo = (this->*funcPtr)();");
			WriteLine("\t\treturn this->m_lastDecodedInfo;");
			WriteLine("\t}");

			WriteLine("\tvoid Print() {");
			WriteLine("");
			WriteLine("\t\tswitch(this->m_templateId) {");
			List<DecodeMessageInfo> messages = GetDecodeMessageMethods(templatesNode);
			foreach(DecodeMessageInfo info in messages) {
				WriteLine("\t\t\tcase " + info.TemplateId + ":");
				WriteLine("\t\t\t\t" + info.PrintMethodName + "((" + info.StructName + "*)this->m_lastDecodedInfo);");
				WriteLine("\t\t\t\tbreak;");
			}
			WriteLine("\t\t}");
			WriteLine("\t}");

			WriteLine("\tvoid PrintXml() {");
			WriteLine("");
			WriteLine("\t\tswitch(this->m_templateId) {");
			foreach(DecodeMessageInfo info in messages) {
				WriteLine("\t\t\tcase " + info.TemplateId + ":");
				WriteLine("\t\t\t\t" + info.PrintXmlMethodName + "((" + info.StructName + "*)this->m_lastDecodedInfo);");
				WriteLine("\t\t\t\tbreak;");
			}
			WriteLine("\t\t}");
			WriteLine("\t}");

			WriteLine("\tinline FastSnapshotInfo* GetSnapshotInfo() {");
			WriteLine("\t\tthis->DecodeHeader();");
			WriteLine("\t\tFastGetSnapshotInfoMethodPointer funcPtr = this->GetSnapshotInfoMethods[this->m_templateId - " + minId + "];");
			WriteLine("\t\treturn (this->*funcPtr)();");
			WriteLine("\t}");
		}

		private  List<DecodeMessageInfo> GetDecodeMessageMethods (XmlNode templatesNode) {
			List<DecodeMessageInfo> res = new List<DecodeMessageInfo>();
			foreach(XmlNode node in templatesNode.ChildNodes) {
				if(node.Name != "template")
					continue;
				DecodeMessageInfo info = new DecodeMessageInfo();
				info.MsgType = node.Attributes["name"].Value.Substring(0, 1);
				info.TemplateId = Int32.Parse(node.Attributes["id"].Value);
				info.NameCore = GetTemplateName(node.PreviousSibling.Value);
				info.HasGetSnapshotInfoMethod = node.PreviousSibling.Value.Contains("Snapshot");
				res.Add(info);
			}
			return res;
		}

		string GetMethodSuffix (XmlNode node) {
			if(!node.Attributes["name"].Value.Contains('-'))
				return string.Empty;
			return node.Attributes["name"].Value.Substring(node.Attributes["name"].Value.IndexOf('-')).Replace('-', '_');
		}

		private  List<string> GetDecodeEntryMethodList (XmlNode templatesNode) {
			List<string> res = new List<string>();
			foreach(XmlNode node in templatesNode.ChildNodes) {
				if(node.Name != "template")
					continue;
				if(node.Attributes["name"].Value.Contains('-')) {
					string name = GetMethodSuffix(node);
					if(!res.Contains(name))
						res.Add(name);
				}
			}
			return res;
		}

		private void WritePointerCode(StructureInfo info) {
			WriteLine("\tLinkedPointer<" + info.Name + ">" + StuctFieldsSpacing + "*Pointer;");
			WriteLine("\tAutoAllocatePointerList<" + info.Name + ">" + StuctFieldsSpacing + "*Allocator;");
			WriteLine("\tbool" + StuctFieldsSpacing + "Used;");
		}

		private  void WriteStructureFieldsDefinitionCode (StructureInfo info, string parentName) {
			WritePresenceMapDefinition();
			WriteNullMapDefinition();
			WritePointerCode(info);
			foreach(XmlNode field in info.Fields) {
				if(field.Name == "string")
					WriteStringDefinition(field);
				else if(field.Name == "uInt32")
					WriteUint32Field(field);
				else if(field.Name == "int32")
					WriteInt32Field(field);
				else if(field.Name == "uInt64")
					WriteUint64Field(field);
				else if(field.Name == "int64")
					WriteInt64Field(field);
				else if(field.Name == "decimal")
					WriteDecimalField(field);
				else if(field.Name == "byteVector")
					WriteByteVectorField(field);
				else if(field.Name == "sequence")
					WriteSequence(field, parentName);
				else if(field.Name == "length") { 
					// Do nothing
				} else
					Console.WriteLine("found undefined field " + field.Name);
			}

			WriteLine("");
			WriteLine("\t" + info.Name + "(){");
			WriteLine("\t\tthis->Used = false;");
			WriteLine("\t\tthis->Pointer = 0;");
			WriteLine("\t\tthis->Allocator = 0;");
			WriteClearFieldsCode(info);
			WriteLine("\t}");
			WriteLine("\t~" + info.Name + "(){ }");
			WriteClearCode(info);
		}

		private void WriteClearFieldsCode(StructureInfo info) {
			WriteLine("\t\tthis->PresenceMap = 0;");
			WriteLine("\t\tthis->NullMap = 0;");
			foreach(XmlNode field in info.Fields) {
				if(field.Name == "string")
					WriteClearStringCode(field);
				if(field.Name == "sequence")
					WriteLine("\t\tthis->" + Name(field) + "Count = 0;");
			}
		}

		private void WriteClearStringCode(XmlNode field) {
			WriteLine("\t\tthis->" + Name(field) + "[0] = '\\0';");
			WriteLine("\t\tthis->" + Name(field) + "Length = 0;");
		}

		private void WriteClearCode(StructureInfo info) {
			WriteLine("\tinline void Clear() {");

			//WriteClearFieldsCode(info);

			WriteLine("\t\tthis->Used = false;");
			WriteLine("\t\tthis->Allocator->FreeItem(this->Pointer);");
			foreach(XmlNode field in info.Fields) {
				if(field.Name != "sequence")
					continue;
				WriteLine("\t\tfor(int i = 0; i < this->" + Name(field) + "Count; i++)");
				WriteLine("\t\t\tthis->" + Name(field) + "[i]->Clear();");
			}
			WriteLine("\t}");			

			WriteLine("\tinline void ReleaseUnused() {");
			WriteLine("\t\tif(this->Used)");
			WriteLine("\t\t\treturn;");
			WriteLine("");
			WriteLine("\t\tthis->Allocator->FreeItem(this->Pointer);");
			foreach(XmlNode field in info.Fields) {
				if(field.Name != "sequence")
					continue;
				WriteLine("\t\tfor(int i = 0; i < this->" + Name(field) + "Count; i++)");
				WriteLine("\t\t\tthis->" + Name(field) + "[i]->ReleaseUnused();");
			}
			WriteLine("\t}");			
		}

		string StuctFieldsSpacing { get{ return "\t\t\t\t\t\t\t"; } }

		private  void WritePresenceMapDefinition () {
			WriteLine("\tUINT64" + StuctFieldsSpacing + "PresenceMap;");
		}

		private  void WriteNullMapDefinition () {
			WriteLine("\tUINT64" + StuctFieldsSpacing + "NullMap;");
		}

		int CalcPresenceMapByteCount(XmlNode node) {
			int maxPresenceBitCount = GetMaxPresenceBitCount(node);
			return CalcPresenceMapByteCount(maxPresenceBitCount);
		}

		int CalcPresenceMapIntCount(XmlNode node) {
			int maxPresenceBitCount = GetMaxPresenceBitCount(node);
			return CalcPresenceMapIntCount(maxPresenceBitCount);
		}

		int CalcPresenceMapIntCount(int bitCount) {
			int res = CalcPresenceMapByteCount(bitCount);
			int intRes = res / 4;
			if(res % 4 > 0)
				intRes++;
			if(intRes == 0)
				return 1;
			return intRes;
		}

		int CalcPresenceMapByteCount(int bitCount) {
			int res = bitCount / 8;
			if(bitCount % 8 > 0)
				res++;
			return res;
		}

		bool FieldMandatoryAndHasConstant (XmlNode field) {
			if(field.ChildNodes.Count == 1 && field.ChildNodes[0].Name == "constant")
				return true;
			return false;
		}

		string GetFieldConstantValue (XmlNode field) { 
			if(!FieldMandatoryAndHasConstant(field))
				return string.Empty;
			return field.ChildNodes[0].Attributes["value"].Value;
		}

		string GetCommentLine (XmlNode field) {
			string result = string.Empty;

			foreach(XmlAttribute attribute in field.Attributes) { 
				if(attribute.Name == "name")
					continue;
				if(!IsKnownAttribute(attribute))
					Console.WriteLine("\nERROR: unknown attribute");
				result += attribute.Name + "=" + attribute.Value + "  ";
			}
			if(field.Name != "sequence") {
				foreach(XmlNode child in field.ChildNodes) { 
					result += "  " + child.Name + (child.Value != null ? "=" + child.Value.ToString() : "");
				}
			}
			if(FieldMandatoryAndHasConstant(field))
				result += " has constant value = " + GetFieldConstantValue(field);
			return string.IsNullOrEmpty(result) ? result : "\t\t\t// " + result;
		}

		private  bool IsKnownAttribute (XmlAttribute attribute) {
			return attribute.Name == "name" || attribute.Name == "id" || attribute.Name == "presence";
		}
		StructureInfo GetOriginalStruct(XmlNode field) {
			if(field.ParentNode == null || field.ParentNode.Attributes["name"] == null)
				return null;
			//Console.WriteLine("Get original struct for " + field.ParentNode.Attributes["name"].Value);
			foreach(StructureInfo info in Structures) {
				if(info.HasIncrementalStruct(field))
					return info;
			}
			return null;
		}
		StructureInfo GetStruct(XmlNode field) {
			foreach(StructureInfo info in Structures) {
				if(info.Node == field)
					return info;
			}
			return null;
		}

		private  void WriteSequence (XmlNode field, string parentName) {
			WriteLine("\tint" + StuctFieldsSpacing + Name(field) + "Count;" + GetCommentLine(field));
			StructureInfo originalStruct = GetOriginalStruct(field);
			if(originalStruct != null) {
				WriteLine("\t" + originalStruct.Name + "* " + Name(field) + "[256];" + GetCommentLine(field));
			}
			else
				WriteLine("\tFast" + parentName + ItemName(field) + "ItemInfo* " + Name(field) + "[256];" + GetCommentLine(field));
		}

		private  void WriteByteVectorField (XmlNode field) {
			WriteByteVectorDefinitionCore(field, StuctFieldsSpacing);
			//WriteLine("\tBYTE*" + StuctFieldsSpacing + Name(field) + ";" + GetCommentLine(field));
			//WriteLine("\tint" + StuctFieldsSpacing + Name(field) + "Length;");
		}

		private  void WriteDecimalField (XmlNode field) {
			WriteLine("\tDecimal" + StuctFieldsSpacing + Name(field) + ";" + GetCommentLine(field));
		}

		private  void WriteInt64Field (XmlNode field) {
			WriteLine("\tUINT64" + StuctFieldsSpacing + Name(field) + ";" + GetCommentLine(field));
		}

		private  void WriteUint64Field (XmlNode field) {
			WriteLine("\tUINT64" + StuctFieldsSpacing + Name(field) + ";" + GetCommentLine(field));
		}

		private  void WriteInt32Field (XmlNode field) {
			WriteLine("\tINT32" + StuctFieldsSpacing + Name(field) + ";" + GetCommentLine(field));
		}

		private  void WriteUint32Field (XmlNode field) {
			WriteLine("\tUINT32" + StuctFieldsSpacing + Name(field) + ";" + GetCommentLine(field));
		}

		private  void WriteStringDefinition (XmlNode field) {
			WriteStringDefinitionCore(field, StuctFieldsSpacing);
			//WriteLine("\tchar*" + StuctFieldsSpacing + Name(field) + ";" + GetCommentLine(field));
			//WriteLine("\tint" + StuctFieldsSpacing + Name(field) + "Length;");
		}

		string GetTemplateName (string templateName) {
			templateName = templateName.Replace("-", "");
			templateName = templateName.Replace("/", "");
			templateName = templateName.Replace(" ", "");
			templateName = templateName.Replace("Full", "");
			templateName = templateName.Replace("Market", "");
			templateName = templateName.Replace("Data", "");
			templateName = templateName.Replace("Snapshot", "");
			templateName = templateName.Replace("Refresh", "");
			return templateName;
		}

		private  void WriteStructureDefinition (StructureInfo info) { 
			WriteLine("class " + info.Name + "{");
			WriteLine("public:");
			WriteStructureFieldsDefinitionCode(info, info.NameCore);
			WriteLine("};");
			WriteLine("");
		}

		void WriteParsePresenceMap (XmlNode node, string info, string tabString) {
			WriteLine(tabString + "this->ParsePresenceMap(&(" + info + "->PresenceMap));");
		}

		private  int GetMaxPresenceBitCount (XmlNode node) {
			int count = 0;
			foreach(XmlNode field in node.ChildNodes)
				if(ShouldWriteCheckPresenceMapCode(field))
					count++;
			return count;
		}

		bool IsValueBelongsToHeader(XmlNode value) {
			if(value.Attributes["id"] == null)
				return false;
			return HeaderTags.Contains(value.Attributes["id"].Value);
		}

		private void WriteCopyPresenceMap(string tabs, string infoName) {
			WriteLine(tabs + infoName + "->PresenceMap = this->m_presenceMap;");
		}

		private  void ParseTemplateNode(XmlNode template, string templateName) {
			WriteLine("\tvoid* Decode" + templateName + "() {");
			StructureInfo info = new StructureInfo() { Node = template, NameCore = templateName };
			WriteLine("\t\tFast" + templateName + "Info* info = " + info.GetFreeMethodName + "();");
			WriteCopyPresenceMap("\t\t", "info");
			WriteLine("");
			foreach(XmlNode value in template.ChildNodes) {
				ParseValue(info, value, "info", templateName, "\t\t");
			}
			WriteLine("\t\tthis->" + info.PrevValueName + " = info;");
			WriteLine("\t\treturn info;");
			WriteLine("\t}");
		}

		List<SnapshotFieldInfo> snapshotInfoFields;
		public class SnapshotFieldInfo { 
			public SnapshotFieldInfo(string fieldType, string fieldName) {
				FieldType = fieldType;
				FieldName = fieldName;
			}
			public string FieldType { get; set; }
			public string FieldName { get; set; }
		}
		protected List<SnapshotFieldInfo> SnapshotInfoFields { 
			get;
			set;
		}

		private XmlNode GetChildNode(XmlNode root, string childName) {
			foreach(XmlNode node in root.ChildNodes) {
				if(node.Attributes["name"].Value == childName)
					return node;
			}
			return null;
		} 

		private void InitializeSnapshotInfoFields(XmlNode templates) {
			List<XmlNode> nodes = GetTemplates(templates);
			foreach(SnapshotFieldInfo info in SnapshotInfoFields) {
				foreach(XmlNode node in nodes) {
					XmlNode child = GetChildNode(node, info.FieldName);
					if(child != null) {
						info.FieldType = child.Name.ToUpper();
						break;
					}
				}
			}
		}

		private bool IsSnapshotNode(XmlNode node) {
			foreach(SnapshotFieldInfo field in SnapshotInfoFields) {
				if(field.FieldName == node.Attributes["name"].Value)
					return true;
			}
			return false;
		}

		private bool HasSnapshotFields(XmlNode template) {
			foreach(XmlNode node in template.ChildNodes) {
				if(IsSnapshotNode(node))
					return true;
			}
			return false;
		}

		private bool HasField(XmlNode template, string name) {
			foreach(XmlNode node in template.ChildNodes) {
				if(node.Attributes["name"].Value == name)
					return true;
			}
			return false;
		}

		private void WriteGetTotNumReportsMethod(XmlNode template) {
			bool found = false;
			string templateName = "";
			foreach(XmlNode node in template.ChildNodes) {
				if(node.Name != "template")
					continue;
				templateName = GetTemplateName(node.PreviousSibling.Value);
				if(templateName.Contains("SecurityDefinition")) {
					found = true;
					template = node;
					break;
				}
			}

			if(!found) {
				throw new Exception("Symbol Template not found");
			}

			WriteLine("\tint GetTotalNumReports() {");
			if(!HasField(template, "TotNumReports"))
				throw new Exception("There is no TotNumReports field in " + templateName + " template");
			WriteLine("\t\t// ReadMsgNumber and DecodeHeader should be called first");
			foreach(XmlNode value in template.ChildNodes) {
				string name = Name(value);
				if(value.Name == "sequence") {
					throw new Exception("Sequence exceeded. TotNumReports not found");
				}
				if(!CanParseValue(value))
					continue;
				if(name != "TotNumReports") {
					WriteSkipCode("\t\t", name);
					continue;
				}
				if(HasOptionalPresence(value))
						WriteLine("\t\treturn ReadInt32_Optional();");
					else
						WriteLine("\t\treturn ReadInt32_Mandatory();");
				break;
			}
			WriteLine("\t}");	
		}

		private  void WriteGetSnapshotInfoMethod(XmlNode template, string templateName) {
			List<string> parsed = new List<string>();

			WriteLine("\tFastSnapshotInfo* GetSnapshotInfo" + templateName + "() {");

			if(!HasSnapshotFields(template)) {
				WriteLine("\t\treturn NULL;");
				WriteLine("\t}");
				return;
			}

			WriteLine("\t\tFastSnapshotInfo *info = GetFreeSnapshotInfo();" );
			WriteCopyPresenceMap("\t\t", "info");
			WriteLine("\t\tinfo->TemplateId = this->m_templateId;");
			WriteLine("");
			StructureInfo info = new StructureInfo() { Node = template, NameCore = templateName }; 
			foreach(XmlNode value in template.ChildNodes) {
				ParseValue(info, value, "info", templateName, "\t\t", true, SnapshotInfoFields, parsed);
				if(parsed.Count == SnapshotInfoFields.Count)
					break;
			}
			WriteLine("\t\treturn info;");
			WriteLine("\t}");

			CurrentFile.Line -= 3;
			while(CurrentFile.Lines[CurrentFile.Line].Contains("SkipToNextField")) {
				CurrentFile.Lines.RemoveAt(CurrentFile.Line);
				CurrentFile.Line--;
			}
			CurrentFile.Line += 3;
		}

		private void WritePrintPresenceMap(XmlNode template, StructureInfo info, string tabs, int tabsCount) {
			if(GetMaxPresenceBitCount(template) > 0) {
				WriteLine(tabs + "PrintPresenceMap(" + info.ValueName + "->PresenceMap, " + GetMaxPresenceBitCount(template) + ", " + tabsCount + ");");
			}
		}

		private void WritePrintXmlPresenceMap(XmlNode template, StructureInfo info, string tabs) {
			if(GetMaxPresenceBitCount(template) > 0) {
				WriteLine(tabs + "PrintXmlPresenceMap(" + info.ValueName + "->PresenceMap, " + GetMaxPresenceBitCount(template) + ");");
			}
		}

		private void PrintDeclareTemplateNode(XmlNode template, string templateName) {
			StructureInfo info = new StructureInfo() { NameCore = templateName };
			WriteLine("\tvoid Print" + templateName + "(" + info.Name + " *info);");
		}
		private void PrintXmlDeclareTemplateNode(XmlNode template, string templateName) {
			StructureInfo info = new StructureInfo() { NameCore = templateName };
			WriteLine("\tvoid PrintXml" + templateName + "(" + info.Name + " *info);");
		}

		private  void PrintTemplateNode (XmlNode template, string templateName) {
			StructureInfo info = new StructureInfo() { NameCore = templateName };
			WriteLine("void FastProtocolManager::Print" + templateName + "(" + info.Name + " *info) {");
			WriteLine("");
			WriteLine("\tprintf(\"" + info.Name + " {\\n\");");
			WritePrintPresenceMap(template, info, "\t\t", 1);
			WriteLine("\tPrintInt32(\"TemplateId\", " + template.Attributes["id"].Value + ", 1);");
			foreach(XmlNode value in template.ChildNodes) {
				PrintValue(value, "info", templateName, "\t", 1);
			}
			WriteLine("\tprintf(\"}\\n\");");
			WriteLine("}");
		}

		private  void PrintXmlTemplateNode (XmlNode template, string templateName) {
			StructureInfo info = new StructureInfo() { NameCore = templateName };
			WriteLine("void FastProtocolManager::PrintXml" + templateName + "(" + info.Name + " *info) {");
			WriteLine("");
			WriteLine("\tPrintXmlItemBegin(\"" + info.Name +"\");");
			WritePrintXmlPresenceMap(template, info, "\t\t");
			WriteLine("\tPrintXmlInt32(\"TemplateId\", " + template.Attributes["id"].Value + ");");
			foreach(XmlNode value in template.ChildNodes) {
				PrintXmlValue(value, "info", templateName, "\t");
			}
			WriteLine("\tPrintXmlItemEnd(\"" + info.Name +"\");");
			WriteLine("}");
		}

		bool HasAttribute (XmlNode node, string attributeName) {
			foreach(XmlAttribute attr in node.Attributes)
				if(attr.Name == attributeName)
					return true;
			if(node.Name == "sequence")
				return false;
			foreach(XmlNode child in node.ChildNodes) {
				if(child.Name == attributeName)
					return true;
			}
			return false;
		}

		private  void WriteCheckingPresenceMapCode (XmlNode value, string objectValueName, string classCoreName, string tabString) {
			int fieldPresenceIndex = CalcFieldPresenceIndex(value);
			if(HasOptionalPresence(value)) {
				WriteLine(tabString + "if(CheckOptionalFieldPresence(" + objectValueName + "->PresenceMap, PRESENCE_MAP_INDEX" + fieldPresenceIndex + ")) {");
			} else {
				WriteLine(tabString + "if(CheckMandatoryFieldPresence(" + objectValueName + "->PresenceMap, PRESENCE_MAP_INDEX" + fieldPresenceIndex + ")) {");
			}
		}

		private  void WriteIncrementOpearatorCode (XmlNode value, string structName, string parentName, string tabString) {
			WriteLine(tabString + "else {");
			WriteLine(tabString + "\t" + structName + "->" + Name(value) + "++;");
			WriteLine(tabString + "}");
		}

		private  bool HasTailAttribute (XmlNode value) {
			return HasChildNode(value, "tail");
		}

		private  bool HasIncrementValueAttribute (XmlNode value) {
			return HasChildNode(value, "increment");
		}

		private  bool HasCopyValueAttribute (XmlNode value) {
			return HasChildNode(value, "copy");
		}

		private  bool HasDefaultValueAttribute (XmlNode value) {
			return HasChildNode(value, "default");
		}

		private  bool HasConstantAttribute (XmlNode value) {
			return HasChildNode(value, "constant");
		}

		private  bool HasOptionalPresence (XmlNode value) {
			return HasAttribute(value, "presence") && value.Attributes["presence"].Value == "optional";
		}

		private  bool HasMandatoryPresence (XmlNode value) {
			return !HasAttribute(value, "presence") || value.Attributes["presence"].Value == "mandatory";
		}

		private  bool HasChildNode (XmlNode value, string name) { 
			foreach(XmlNode node in value.ChildNodes) {
				if(node.Name == name)
					return true;
			}
			return false;
		}

		private  XmlNode GetHasChildNode (XmlNode value, string name) {
			foreach(XmlNode node in value.ChildNodes) {
				if(node.Name == name)
					return node;
			}
			return null;
		}

		private  int CalcFieldPresenceIndex (XmlNode value) {
			int index = 0;
			XmlNode parentNode = value.ParentNode;
			foreach(XmlNode node in parentNode.ChildNodes) { 
				if(node == value)
					return index;
				if(ShouldWriteCheckPresenceMapCode(node))
					index++;
			}
			return index;
		}

		private  int CalcNullIndex (XmlNode value) {
			int index = 0;
			XmlNode parentNode = value.ParentNode;
			foreach(XmlNode node in parentNode.ChildNodes) { 
				if(node == value)
					return index;
				if(ShouldWriteNullCheckCode(node))
					index++;
			}
			return index;
		}

		private  bool HasFieldOperator (XmlNode value) {
			return HasConstantAttribute(value) ||
			HasCopyValueAttribute(value) ||
			HasDefaultValueAttribute(value) ||
			HasIncrementValueAttribute(value);
		}

		private  bool ShouldWriteNullCheckCode (XmlNode value) {
			if(HasOptionalPresence(value) && !HasFieldOperator(value))
				return true;
			if(HasDefaultValueAttribute(value) || HasCopyValueAttribute(value) || HasIncrementValueAttribute(value)) {
				if(HasOptionalPresence(value))
					return true;
			}
			return false;
		}

		private  bool ShouldWriteCheckPresenceMapCode (XmlNode value) {
			string[] forbidden = new string[] { "MsgSeqNum", "MessageEncoding" };
			for(int i = 0; i < forbidden.Length; i++) {
				if(forbidden[i] == Name(value))
					return false;
			}

			if(HasMandatoryPresence(value) && HasConstantAttribute(value))
				return false;
			if(HasOptionalPresence(value) && HasConstantAttribute(value))
				return true;
			if(HasMandatoryPresence(value) &&
			   !HasCopyValueAttribute(value) &&
			   !HasDefaultValueAttribute(value) &&
			   !HasIncrementValueAttribute(value))
				return false;
			if(HasOptionalPresence(value) && !HasFieldOperator(value)) {
				return false;
			}
			if(HasMandatoryPresence(value)) {
				if(HasCopyValueAttribute(value) || HasDefaultValueAttribute(value) || HasIncrementValueAttribute(value))
					return true;
			}
			if(HasOptionalPresence(value)) {
				if(HasCopyValueAttribute(value) || HasDefaultValueAttribute(value) || HasIncrementValueAttribute(value))
					return true;
			}
			return false;
		}

		private  string GetDefaultValue (XmlNode value) {
			foreach(XmlNode node in value.ChildNodes) {
				if(node.Name == "default")
					return node.Attributes["value"].Value;
			}
			return string.Empty;
		}

		private  void WriteConstantValueCheckingCode (XmlNode value, string structName, string parentName, string tabString) {
			if(!WriteConstantCheckingCode)
				return;
			//WriteLine("#ifdef FAST_CHECK_CONSTANT_VALUES");
			if(value.Name == "string")
				WriteStringConstantValueCheckngCode(value, structName, parentName, tabString);
			else
				WriteNumericValueConstantCheckingCode(value, structName, parentName, tabString);
			//WriteLine("#endif");
		}

		private  void WriteNumericValueConstantCheckingCode (XmlNode value, string structName, string parentName, string tabString) {
			WriteLine(tabString + "if(" + structName + "->" + Name(value) + " != " + GetFieldConstantValue(value) + ") this->LogError(\"" + structName + "::" + Name(value) + " != " + GetFieldConstantValue(value) + "\");");
		}

		private  void WriteStringConstantValueCheckngCode (XmlNode value, string structName, string parentName, string tabString) {
			WriteLine(tabString + "if(!this->FastCompareString("
			+ structName + "->" + Name(value) + ", " + structName + "->" + Name(value) + "Length, " +
			"\"" + GetFieldConstantValue(value) + "\"" + ", " + GetFieldConstantValue(value).Count() + ""
			+ ")) this->LogError(\"" + parentName + "Info::" + Name(value) + " != " + GetFieldConstantValue(value) + "\");");
		}
		bool ShouldSkipField(XmlNode node) {
			return node.Attributes["skip"] != null && node.Attributes["skip"].Value.ToLower() == "true";
		}
		string Name (XmlNode node) {
			return node.Attributes["name"] != null ? node.Attributes["name"].Value : "";
		}
		string ItemName(XmlNode node) {
			return Name(node) == "GroupMDEntries" ? "" : Name(node);
		}
		string PresenceIndexName(XmlNode node) {
			return Name(node) + "PresenceIndex";
		}
		string NullFlagName(XmlNode node) {
			return "IsNull" + Name(node);
		}

		int LevelCount = 1;

		string GetIemInfoPrefix (XmlNode value) {
			string prefix = Name(value);
			StringBuilder builder = new StringBuilder();
			foreach(char c in prefix)
				if(Char.IsUpper(c))
					builder.Append(c);
			return builder.ToString().ToLower();
		}

		private  void ParseSequence (StructureInfo str, XmlNode value, string objectValueName, string parentClassCoreName, string tabString) {
			StructureInfo info = GetOriginalStruct(value);
			if(info == null)
				info = GetStruct(value);
			if(info == null) {
				Console.WriteLine("Error: no struct found for " + value.ParentNode.Attributes["name"].Value);
			}
			string itemInfo = GetIemInfoPrefix(value) + "ItemInfo";
			WriteLine("");
			if(ShouldWriteNullCheckCode(value)) {
				WriteLine(tabString + "if(CheckProcessNullInt32()) {");
				WriteLine(tabString + "\t" + objectValueName + "->" + Name(value) + "Count = 0;");
				WriteLine(tabString + "\t" + objectValueName + "->NullMap |= NULL_MAP_INDEX" + CalcNullIndex(value) + ";");
				WriteLine(tabString + "}");
				WriteLine(tabString + "else");
				tabString += "\t";
			}
			if(HasOptionalPresence(value))
				WriteLine(tabString + objectValueName + "->" + Name(value) + "Count = ReadUInt32_Optional();");
			else 				
				WriteLine(tabString + objectValueName + "->" + Name(value) + "Count = ReadUInt32_Mandatory();");
			if(ShouldWriteNullCheckCode(value)) {
				tabString = tabString.Substring(1);
			}
			WriteLine(tabString + info.Name + "* " + itemInfo + " = NULL;");
			WriteLine("");
			WriteLine(tabString + "for(int i = 0; i < " + objectValueName + "->" + Name(value) + "Count; i++) {");
			WriteLine(tabString + "\t" + itemInfo + " = GetFree" + info.NameCore + "ItemInfo();");
			WriteLine(tabString + "\t" + objectValueName + "->" + Name(value) + "[i] = " + itemInfo + ";");

			if(GetMaxPresenceBitCount(value) > 0) {
				WriteLine("");
				WriteParsePresenceMap(value, itemInfo, tabString + "\t");
				WriteLine("");
			}

			foreach(XmlNode node in value.ChildNodes) {
				if(node.Name == "length")
					continue;
				LevelCount++;
				ParseValue(info, node, itemInfo, parentClassCoreName + Name(value), tabString + "\t");
				LevelCount--;
			}
			WriteLine(tabString + "\tthis->" + info.PrevValueName + " = " + itemInfo + ";");
			WriteLine(tabString + "}");
			WriteLine("");
		}

		private  bool ExtendedDecimal (XmlNode value) {
			foreach(XmlNode node in value.ChildNodes)
				if(node.Name == "exponent" || node.Name == "mantissa")
					return true;
			return false;
		}

		private  void ParseByteVectorValue (StructureInfo str, XmlNode value, string info, string tabString) {
			if(ShouldWriteNullCheckCode(value)) {
				WriteLine(tabString + "if(CheckProcessNullByteVector())");
				WriteLine(tabString + "\t" + info + "->NullMap |= NULL_MAP_INDEX" + CalcNullIndex(value) + ";");
				WriteLine(tabString + "else");
				tabString += "\t";
			}
			if(ShouldSkipField(value)) {
				WriteLine(tabString + "{");
				WriteLine(tabString + "\tSkipToNextField(); // " + Name(value) + " Length");
				WriteLine(tabString + "\tSkipToNextField(); // " + Name(value) + " Data");
				WriteLine(tabString + "}");
			} else {
				if(HasOptionalPresence(value))
					WriteLine(tabString + "ReadByteVector_Optional(" + info + "->" + Name(value) + ", &(" + info + "->" + Name(value) + "Length)" + ", " + GetMaxByteVectorSize(value) + ");");
				else
					WriteLine(tabString + "ReadByteVector_Mandatory(" + info + "->" + Name(value) + ", &(" + info + "->" + Name(value) + "Length)" + ", " + GetMaxByteVectorSize(value) + ");");
			}
			if(ShouldWriteNullCheckCode(value)) {
				tabString = tabString.Substring(1);
				/*
				if(HasOperators(value)) {
					WriteLine(tabString + "else {");
					tabString += "\t";
					WriteByteVectorValueOperatorsCode(str, value, info, tabString);
					tabString = tabString.Substring(1);
					WriteLine(tabString + "}");
				}*/
			}
		}

		private  void ParseDecimalValue (StructureInfo str, XmlNode value, string info, string tabString) {
			if(ShouldWriteNullCheckCode(value)) {
				WriteLine(tabString + "if(CheckProcessNullDecimal())");
				WriteLine(tabString + "\t" + info + "->NullMap |= NULL_MAP_INDEX" + CalcNullIndex(value) + ";");
				WriteLine(tabString + "else");
				tabString += "\t";
			}
			if(ExtendedDecimal(value))
				throw new Exception("Extended deciamal detected in template!");
			if(ShouldSkipField(value)) {
				WriteLine(tabString + "{");
				WriteLine(tabString + "\tSkipToNextField(); // " + Name(value) + " Mantissa");
				WriteLine(tabString + "\tSkipToNextField(); // " + Name(value) + " Exponent");
				WriteLine(tabString + "}");
			} else {
				if(HasOptionalPresence(value))
					WriteLine(tabString + "ReadDecimal_Optional(&(" + info + "->" + Name(value) + "));");
				else
					WriteLine(tabString + "ReadDecimal_Mandatory(&(" + info + "->" + Name(value) + "));");
			}
			if(ShouldWriteNullCheckCode(value)) {
				tabString = tabString.Substring(1);
				/*
				if(HasOperators(value)) {
					WriteLine(tabString + "else {");
					tabString += "\t";
					WriteDecimalValueOperatorsCode(str, value, info, tabString);
					tabString = tabString.Substring(1);
					WriteLine(tabString + "}");
				}
				*/
			}
		}

		private  void ParseInt64Value (StructureInfo str, XmlNode value, string info, string tabString) {
			if(ShouldWriteNullCheckCode(value)) {
				WriteLine(tabString + "if(CheckProcessNullInt64())");
				WriteLine(tabString + "\t" + info + "->NullMap |= NULL_MAP_INDEX" + CalcNullIndex(value) + ";");
				WriteLine(tabString + "else");
				tabString += "\t";
			}
			if(ShouldSkipField(value)) {
				WriteLine(tabString + "SkipToNextField(); // " + Name(value));
			} else {
				if(HasOptionalPresence(value))
					WriteLine(tabString + info + "->" + Name(value) + " = ReadInt64_Optional();");
				else
					WriteLine(tabString + info + "->" + Name(value) + " = ReadInt64_Mandatory();");
			}
			if(ShouldWriteNullCheckCode(value)) {
				tabString = tabString.Substring(1);
				/*
				if(HasOperators(value)) {
					WriteLine(tabString + "else {");
					tabString += "\t";
					WriteInt64ValueOperatorsCode(str, value, info, tabString);
					tabString = tabString.Substring(1);
					WriteLine(tabString + "}");
				}*/
			}
		}

		private  void ParseUint64Value (StructureInfo str, XmlNode value, string info, string tabString) {
			if(ShouldWriteNullCheckCode(value)) {
				WriteLine(tabString + "if(CheckProcessNullUInt64())");
				WriteLine(tabString + "\t" + info + "->NullMap |= NULL_MAP_INDEX" + CalcNullIndex(value) + ";");
				WriteLine(tabString + "else");
				tabString += "\t";
			}
			if(ShouldSkipField(value)) {
				WriteLine(tabString + "SkipToNextField(); // " + Name(value));
			} else {
				if(HasOptionalPresence(value))
					WriteLine(tabString + info + "->" + Name(value) + " = ReadUInt64_Optional();");
				else
					WriteLine(tabString + info + "->" + Name(value) + " = ReadUInt64_Mandatory();");
			}
			if(ShouldWriteNullCheckCode(value)) {
				tabString = tabString.Substring(1);
				/*
				if(HasOperators(value)) {
					WriteLine(tabString + "else {");
					tabString += "\t";
					WriteUint64ValueOperatorsCode(str, value, info, tabString);
					tabString = tabString.Substring(1);
					WriteLine(tabString + "}");
				}*/
			}
		}

		private  void ParseInt32Value (StructureInfo str, XmlNode value, string info, string tabString) {
			if(ShouldWriteNullCheckCode(value)) {
				WriteLine(tabString + "if(CheckProcessNullInt32())");
				WriteLine(tabString + "\t" + info + "->NullMap |= NULL_MAP_INDEX" + CalcNullIndex(value) + ";");
				WriteLine(tabString + "else");
				tabString += "\t";
			}
			if(ShouldSkipField(value)) {
				WriteLine(tabString + "SkipToNextField(); // " + Name(value));
			} else {
				if(HasOptionalPresence(value))
					WriteLine(tabString + info + "->" + Name(value) + " = ReadInt32_Optional();");
				else
					WriteLine(tabString + info + "->" + Name(value) + " = ReadInt32_Mandatory();");
			}
			if(ShouldWriteNullCheckCode(value)) {
				tabString = tabString.Substring(1);
				/*
				if(HasOperators(value)) {
					WriteLine(tabString + "else {");
					tabString += "\t";
					WriteInt32ValueOperatorsCode(str, value, info, tabString);
					tabString = tabString.Substring(1);
					WriteLine(tabString + "}");
				}*/
			}
		}

		private  void ParseUint32Value (StructureInfo str, XmlNode value, string info, string tabString) {
			if(ShouldWriteNullCheckCode(value)) {
				WriteLine(tabString + "if(CheckProcessNullUInt32())");
				WriteLine(tabString + "\t" + info + "->NullMap |= NULL_MAP_INDEX" + CalcNullIndex(value) + ";");
				WriteLine(tabString + "else");
				tabString += "\t";
			}
			if(ShouldSkipField(value)) {
				WriteLine(tabString + "SkipToNextField(); // " + Name(value));
			} else {
				if(HasOptionalPresence(value))
					WriteLine(tabString + info + "->" + Name(value) + " = ReadUInt32_Optional();");
				else
					WriteLine(tabString + info + "->" + Name(value) + " = ReadUInt32_Mandatory();");
			}
			if(ShouldWriteNullCheckCode(value)) {
				tabString = tabString.Substring(1);
				/*
				if(HasOperators(value)) {
					WriteLine(tabString + "else {");
					tabString += "\t";
					WriteUint32ValueOperatorsCode(str, value, info, tabString);
					tabString = tabString.Substring(1);
					WriteLine(tabString + "}");
				}*/
			}
		}

		private  void ParseStringValue (StructureInfo str, XmlNode value, string info, string tabString) {
			if(ShouldWriteNullCheckCode(value)) {
				WriteLine(tabString + "if(CheckProcessNullString())");
				WriteLine(tabString + "\t" + info + "->NullMap |= NULL_MAP_INDEX" + CalcNullIndex(value) + ";");
				WriteLine(tabString + "else");
				tabString += "\t";
			}
			if(ShouldSkipField(value)) {
				WriteLine(tabString + "SkipToNextField(); //" + Name(value));
			} else {
				if(HasOptionalPresence(value))
					WriteLine(tabString + "ReadString_Optional(" + info + "->" + Name(value) + ", &(" + info + "->" + Name(value) + "Length)" + ");");
				else
					WriteLine(tabString + "ReadString_Mandatory(" + info + "->" + Name(value) + ", &(" + info + "->" + Name(value) + "Length)" + ");");
			}
			if(ShouldWriteNullCheckCode(value)) {
				tabString = tabString.Substring(1);
				/*
				if(HasOperators(value)) {
					WriteLine(tabString + "else {");
					tabString += "\t";
					WriteStringValueOperatorsCode(str, value, info, tabString);
					tabString = tabString.Substring(1);
					WriteLine(tabString + "}");
				}
				*/
			}
		}

		private  void WriteDecimalValueDefault (XmlNode value, string structName, string tabString) {
			WriteLine(tabString + structName + "->" + Name(value) + " = " + GetDefaultValue(value) + ";");
		}

		private  void WriteInt64ValueDefault (XmlNode value, string structName, string tabString) {
			WriteLine(tabString + structName + "->" + Name(value) + " = " + GetDefaultValue(value) + ";");
		}

		private  void WriteUint64ValueDefault (XmlNode value, string structName, string tabString) {
			WriteLine(tabString + structName + "->" + Name(value) + " = " + GetDefaultValue(value) + ";");
		}

		private  void WriteInt32ValueDefault (XmlNode value, string structName, string tabString) {
			WriteLine(tabString + structName + "->" + Name(value) + " = " + GetDefaultValue(value) + ";");
		}

		private  void WriteUint32ValueDefault (XmlNode value, string structName, string tabString) {
			WriteLine(tabString + structName + "->" + Name(value) + " = " + GetDefaultValue(value) + ";");
		}

		private  void WriteStringValueDefault (XmlNode value, string structName, string tabString) {
			ConstantStringInfo info = ConstantStrings.FirstOrDefault((i) => i.Node == value);
			WriteLine(tabString + structName + "->" + Name(value) + " = this->" + info.FieldName + ";");
			WriteLine(tabString + structName + "->" + Name(value) + "Length = " + GetDefaultValue(value).Length + ";");
		}

		private  void WriteUint32ValueOperatorsCode (StructureInfo str, XmlNode value, string info, string tabString) {
			if(HasDefaultValueAttribute(value)) {
				WriteUint32ValueDefault(value, info, tabString);
			}
			if(HasCopyValueAttribute(value)) {
				WriteSetCopyFlagCode(str, value, info, tabString);
			}
			if(HasIncrementValueAttribute(value)) {
				WriteSimpleIncrementValueCode(value, info, tabString);
			}
		}

		private  void WriteInt32ValueOperatorsCode (StructureInfo str, XmlNode value, string info, string tabString) {
			if(HasDefaultValueAttribute(value)) {
				WriteInt32ValueDefault(value, info, tabString);
			}
			if(HasCopyValueAttribute(value)) {
				WriteSetCopyFlagCode(str, value, info, tabString);
			}
			if(HasIncrementValueAttribute(value)) {
				WriteSimpleIncrementValueCode(value, info, tabString);
			}
		}

		private void WriteSetCopyFlagCode(StructureInfo str, XmlNode value, string info, string tabString) {
			WriteLine(tabString + info + "->" + Name(value) + " = this->" + str.PrevValueName + "->" + Name(value) + ";");
			//WriteLine(tabString + info + "->CopyCount++;");
		}

		private  void WriteDecimalValueOperatorsCode (StructureInfo str, XmlNode value, string info, string tabString) {
			if(HasDefaultValueAttribute(value)) {
				WriteDecimalValueDefault(value, info, tabString);
			}
			if(HasCopyValueAttribute(value)) {
				WriteSetCopyFlagCode(str, value, info, tabString);
			}
			if(HasIncrementValueAttribute(value))
				throw new Exception("TODO Increment decimal");
		}

		private  void WriteDecimalCopyOperatorCode (XmlNode value, string info, string tabString) {
			WriteLine(tabString + "*((UNT64*)&(" + info + "->" + Name(value) + ")) = *((UINT64*)&(" + info + "->Prev" + Name(value) + "));");
		}

		private  void WriteByteVectorValueOperatorsCode (StructureInfo str, XmlNode value, string info, string tabString) {
			if(HasCopyValueAttribute(value)) {
				WriteStringCopyValueCode(str, value, info, tabString);
			}
		}

		private  void WriteInt64ValueOperatorsCode (StructureInfo str, XmlNode value, string info, string tabString) {
			if(HasDefaultValueAttribute(value)) {
				WriteInt64ValueDefault(value, info, tabString);
			}
			if(HasCopyValueAttribute(value)) {
				WriteSetCopyFlagCode(str, value, info, tabString);
			}
			if(HasIncrementValueAttribute(value)) {
				WriteSimpleIncrementValueCode(value, info, tabString);
			}
			if(HasIncrementValueAttribute(value)) {
				WriteSimpleIncrementValueCode(value, info, tabString);
			}
		}

		private  void WriteUint64ValueOperatorsCode (StructureInfo str, XmlNode value, string info, string tabString) {
			if(HasDefaultValueAttribute(value)) {
				WriteUint64ValueDefault(value, info, tabString);
			}
			if(HasCopyValueAttribute(value)) {
				WriteSetCopyFlagCode(str, value, info, tabString);
			}
			if(HasIncrementValueAttribute(value)) {
				WriteSimpleIncrementValueCode(value, info, tabString);
			}
		}

		private  void WriteSimpleIncrementValueCode (XmlNode value, string info, string tabString) {
			WriteLine(tabString + info + "->" + Name(value) + "++;");
		}

		private  void WriteStringValueOperatorsCode (StructureInfo str, XmlNode value, string info, string tabString) {
			if(HasDefaultValueAttribute(value)) { 
				WriteStringValueDefault(value, info, tabString);
			} else if(HasCopyValueAttribute(value)) {
				WriteStringCopyValueCode(str, value, info, tabString);
			}
		}

		private  void WriteStringCopyValueCode (StructureInfo str, XmlNode value, string info, string tabString) {
			WriteLine(tabString + "this->CopyString(" + info + "->" + Name(value) + ", " + str.PrevValueName + "->" + Name(value) + ", " + str.PrevValueName + "->" + Name(value) + "Length" + ");");
			//WriteLine(tabString + info + "->" + Name(value) + " = this->" + str.PrevValueName + "->" + Name(value) + ";");
			WriteLine(tabString + info + "->" + Name(value) + "Length = this->" + str.PrevValueName + "->" + Name(value) + "Length;");
		}

		private bool CanParseValue(XmlNode value) {
			string[] forbidden = { "MessageType", "ApplVerID", "BeginString", "SenderCompID", "MessageEncoding" };
			for(int i = 0; i < forbidden.Length; i++)
				if(forbidden[i] == Name(value))
					return false;
			return true;
		}

		private  void ParseValue (StructureInfo str, XmlNode value, string objectValueName, string classCoreName, string tabString) {
			ParseValue(str, value, objectValueName, classCoreName, tabString, false, null, null);
		}

		private void WriteSkipCode(string tabStrings, string fieldName) {
			WriteLine(tabStrings + "SkipToNextField(); // " + fieldName);
		}
		bool Contains(List<SnapshotFieldInfo> fields, XmlNode node) {
			foreach(SnapshotFieldInfo info in fields) {
				if(info.FieldName == Name(node))
					return true;
			}
			return false;
		}
		private  void ParseValue (StructureInfo str, XmlNode value, string objectValueName, string classCoreName, string tabString, bool skipNonAllowed, List<SnapshotFieldInfo> allowedFields, List<string> parsed) {
			if(value.Name == "length")
				return;

			// skip constant value WHY??????!!!!!
			if(!CanParseValue(value))
				return;
						
			if(skipNonAllowed) { 
				if(!Contains(allowedFields, value)) {
					WriteSkipCode(tabString, Name(value));
					return;
				}
				parsed.Add(Name(value));
			}
			if(ShouldWriteCheckPresenceMapCode(value)) {
				string name = HasOptionalPresence(value)? "CheckOptionalFieldPresence": "CheckMandatoryFieldPresence";
				WriteLine(tabString + "if(" + name + "(" + objectValueName + "->PresenceMap, PRESENCE_MAP_INDEX" + CalcFieldPresenceIndex(value) + ")) {");
				tabString += "\t";
			}
			if(value.Name == "string")
				ParseStringValue(str, value, objectValueName, tabString);
			else if(value.Name == "uInt32")
				ParseUint32Value(str, value, objectValueName, tabString);
			else if(value.Name == "int32")
				ParseInt32Value(str, value, objectValueName, tabString);
			else if(value.Name == "uInt64")
				ParseUint64Value(str, value, objectValueName, tabString);
			else if(value.Name == "int64")
				ParseInt64Value(str, value, objectValueName, tabString);
			else if(value.Name == "decimal")
				ParseDecimalValue(str, value, objectValueName, tabString);
			else if(value.Name == "byteVector")
				ParseByteVectorValue(str, value, objectValueName, tabString);
			else if(value.Name == "sequence")
				ParseSequence(str, value, objectValueName, classCoreName, tabString);
			else {
				WriteLine(tabString + "TODO!!!!!!!!");
				Console.WriteLine("ERROR: found undefined field " + value.Name);
				throw new NotImplementedException("ERROR: found undefined field " + value.Name);
			}
			if(HasConstantAttribute(value))
				WriteConstantValueCheckingCode(value, objectValueName, classCoreName, tabString);
			if(ShouldWriteCheckPresenceMapCode(value)) {
				tabString = tabString.Substring(1);
				WriteLine(tabString + "}");
				WriteLine(tabString + "else {");
				WriteApplyOperatorsCode(str, value, objectValueName, tabString + "\t");
				//WriteLine(tabString + "\t" + objectValueName + "-> Allow" + Name(value) + " = false;");
				WriteLine(tabString + "}");
			}
		}

		private void WriteApplyOperatorsCode(StructureInfo str, XmlNode value, string info, string tabString) {
			if(value.Name == "string")
				WriteStringValueOperatorsCode(str, value, info, tabString);
			else if(value.Name == "uInt32")
				WriteUint32ValueOperatorsCode(str, value, info, tabString);
			else if(value.Name == "int32")
				WriteInt32ValueOperatorsCode(str, value, info, tabString);
			else if(value.Name == "uInt64")
				WriteUint64ValueOperatorsCode(str, value, info, tabString);
			else if(value.Name == "int64")
				WriteInt64ValueOperatorsCode(str, value, info, tabString);
			else if(value.Name == "decimal")
				WriteDecimalValueOperatorsCode(str, value, info, tabString);
			else if(value.Name == "byteVector")
				WriteByteVectorValueOperatorsCode(str, value, info, tabString);
		}

		private  void PrintStringValue (XmlNode value, string info, string tabString, int tabsCount) {
			WriteLine(tabString + "PrintString(\"" + Name(value) + "\", " + info + "->" + Name(value) + ", " + info + "->" + Name(value) + "Length" + ", " + tabsCount + ");");
		}

		private  void PrintUInt32Value (XmlNode value, string info, string tabString, int tabsCount) {
			WriteLine(tabString + "PrintUInt32(\"" + Name(value) + "\", " + info + "->" + Name(value) + ", " + tabsCount + ");");
		}

		private  void PrintInt32Value (XmlNode value, string info, string tabString, int tabsCount) {
			WriteLine(tabString + "PrintInt32(\"" + Name(value) + "\", " + info + "->" + Name(value) + ", " + tabsCount + ");");
		}

		private  void PrintUInt64Value (XmlNode value, string info, string tabString, int tabsCount) {
			WriteLine(tabString + "PrintUInt64(\"" + Name(value) + "\", " + info + "->" + Name(value) + ", " + tabsCount + ");");
		}

		private  void PrintInt64Value (XmlNode value, string info, string tabString, int tabsCount) {
			WriteLine(tabString + "PrintInt64(\"" + Name(value) + "\", " + info + "->" + Name(value) + ", " + tabsCount + ");");
		}

		private  void PrintDecimalValue (XmlNode value, string info, string tabString, int tabsCount) {
			WriteLine(tabString + "PrintDecimal(\"" + Name(value) + "\", &(" + info + "->" + Name(value) + "), " + tabsCount + ");");
		}

		private  void PrintByteVectorValue (XmlNode value, string info, string tabString, int tabsCount) {
			WriteLine(tabString + "PrintByteVector(\"" + Name(value) + "\", " + info + "->" + Name(value) + ", " + info + "->" + Name(value) + "Length, " + tabsCount + ");");
		}

		private  void PrintXmlStringValue (XmlNode value, string info, string tabString) {
			WriteLine(tabString + "PrintXmlString(\"" + Name(value) + "\", " + info + "->" + Name(value) + ", " + info + "->" + Name(value) + "Length" + ");");
		}

		private  void PrintXmlUInt32Value (XmlNode value, string info, string tabString) {
			WriteLine(tabString + "PrintXmlUInt32(\"" + Name(value) + "\", " + info + "->" + Name(value) + ");");
		}

		private  void PrintXmlInt32Value (XmlNode value, string info, string tabString) {
			WriteLine(tabString + "PrintXmlInt32(\"" + Name(value) + "\", " + info + "->" + Name(value) + ");");
		}

		private  void PrintXmlUInt64Value (XmlNode value, string info, string tabString) {
			WriteLine(tabString + "PrintXmlUInt64(\"" + Name(value) + "\", " + info + "->" + Name(value) + ");");
		}

		private  void PrintXmlInt64Value (XmlNode value, string info, string tabString) {
			WriteLine(tabString + "PrintXmlInt64(\"" + Name(value) + "\", " + info + "->" + Name(value) + ");");
		}

		private  void PrintXmlDecimalValue (XmlNode value, string info, string tabString) {
			WriteLine(tabString + "PrintXmlDecimal(\"" + Name(value) + "\", &(" + info + "->" + Name(value) + "));");
		}

		private  void PrintXmlByteVectorValue (XmlNode value, string info, string tabString) {
			WriteLine(tabString + "PrintXmlByteVector(\"" + Name(value) + "\", " + info + "->" + Name(value) + ", " + info + "->" + Name(value) + "Length" + ");");
		}

		private  void PrintXmlSequence (XmlNode value, string objectValueName, string parentClassCoreName, string tabString) {
			StructureInfo info = GetOriginalStruct(value);
			if(info == null)
				info = GetStruct(value);
			string itemInfo = GetIemInfoPrefix(value) + "ItemInfo";
			WriteLine(tabString + "PrintXmlInt32(\"" + Name(value) + "Count\", " + objectValueName + "->" + Name(value) + "Count);");
			WriteLine("");
			string countField = objectValueName + "->" + Name(value) + "Count";

			WriteLine(tabString + info.Name + "* " + itemInfo + " = NULL;");
			WriteLine("");
			WriteLine(tabString + "for(int i = 0; i < " + countField + "; i++) {");
			WriteLine(tabString + "\t" + itemInfo + " = " + objectValueName + "->" + Name(value) + "[i];");
			WriteLine(tabString + "\tPrintXmlItemBegin(\"item\", i);");
			foreach(XmlNode node in value.ChildNodes) {
				if(node.Name == "length")
					continue;
				LevelCount++;
				PrintXmlValue(node, itemInfo, parentClassCoreName + Name(value), tabString + "\t");
				LevelCount--;
			}
			WriteLine(tabString + "\tPrintXmlItemEnd(\"item\", i);");
			WriteLine(tabString + "}");
			WriteLine("");
		}

		private  void PrintSequence (XmlNode value, string objectValueName, string parentClassCoreName, string tabString, int tabsCount) {
			StructureInfo info = GetOriginalStruct(value);
			if(info == null)
				info = GetStruct(value);
			string itemInfo = GetIemInfoPrefix(value) + "ItemInfo";
			WriteLine(tabString + "PrintInt32(\"" + Name(value) + "Count\", " + objectValueName + "->" + Name(value) + "Count, " + tabsCount + ");");
			WriteLine("");
			string countField = objectValueName + "->" + Name(value) + "Count";

			WriteLine(tabString + info.Name + "* " + itemInfo + " = NULL;");
			WriteLine("");
			WriteLine(tabString + "for(int i = 0; i < " + countField + "; i++) {");
			WriteLine(tabString + "\t" + itemInfo + " = " + objectValueName + "->" + Name(value) + "[i];");
			WriteLine(tabString + "\tPrintItemBegin(\"item\", i, " + tabsCount + ");");
			foreach(XmlNode node in value.ChildNodes) {
				if(node.Name == "length")
					continue;
				LevelCount++;
				tabsCount++;
				PrintValue(node, itemInfo, parentClassCoreName + Name(value), tabString + "\t", tabsCount);
				tabsCount--;
				LevelCount--;
			}
			WriteLine(tabString + "\tPrintItemEnd(" + tabsCount + ");");
			WriteLine(tabString + "}");
			WriteLine("");
		}

		private  void PrintValue (XmlNode value, string objectValueName, string classCoreName, string tabString, int tabsCount) {
			if(value.Name == "length")
				return;
			
			// skip constant value WHY??????!!!!!
			if(HasConstantAttribute(value))
				return;
			if(ShouldWriteNullCheckCode(value)) { 
				int nullIndex = CalcNullIndex(value);
				WriteLine(tabString + "if((" + objectValueName + "->NullMap & NULL_MAP_INDEX" + nullIndex + ") != 0)");
				tabString += "\t";
			}

			if(value.Name == "string")
				PrintStringValue(value, objectValueName, tabString, tabsCount);
			else if(value.Name == "uInt32")
				PrintUInt32Value(value, objectValueName, tabString, tabsCount);
			else if(value.Name == "int32")
				PrintInt32Value(value, objectValueName, tabString, tabsCount);
			else if(value.Name == "uInt64")
				PrintUInt64Value(value, objectValueName, tabString, tabsCount);
			else if(value.Name == "int64")
				PrintInt64Value(value, objectValueName, tabString, tabsCount);
			else if(value.Name == "decimal")
				PrintDecimalValue(value, objectValueName, tabString, tabsCount);
			else if(value.Name == "byteVector")
				PrintByteVectorValue(value, objectValueName, tabString, tabsCount);
			else if(value.Name == "sequence")
				PrintSequence(value, objectValueName, classCoreName, tabString, tabsCount);
			else {
				WriteLine(tabString + "TODO!!!!!!!!");
				Console.WriteLine("ERROR: found undefined field " + value.Name);
				throw new NotImplementedException("ERROR: found undefined field " + value.Name);
			}
			if(ShouldWriteNullCheckCode(value))
				tabString = tabString.Substring(1);
		}

		private  void PrintXmlValue (XmlNode value, string objectValueName, string classCoreName, string tabString) {
			if(value.Name == "length")
				return;

			// skip constant value WHY??????!!!!!
			if(HasConstantAttribute(value))
				return;

			if(ShouldWriteNullCheckCode(value)) {
				int nullIndex = CalcNullIndex(value);
				WriteLine(tabString + "if((" + objectValueName + "->NullMap & NULL_MAP_INDEX" + nullIndex + ") != 0)");
				tabString += "\t";
			}
			if(value.Name == "string")
				PrintXmlStringValue(value, objectValueName, tabString);
			else if(value.Name == "uInt32")
				PrintXmlUInt32Value(value, objectValueName, tabString);
			else if(value.Name == "int32")
				PrintXmlInt32Value(value, objectValueName, tabString);
			else if(value.Name == "uInt64")
				PrintXmlUInt64Value(value, objectValueName, tabString);
			else if(value.Name == "int64")
				PrintXmlInt64Value(value, objectValueName, tabString);
			else if(value.Name == "decimal")
				PrintXmlDecimalValue(value, objectValueName, tabString);
			else if(value.Name == "byteVector")
				PrintXmlByteVectorValue(value, objectValueName, tabString);
			else if(value.Name == "sequence")
				PrintXmlSequence(value, objectValueName, classCoreName, tabString);
			else {
				WriteLine(tabString + "TODO!!!!!!!!");
				Console.WriteLine("ERROR: found undefined field " + value.Name);
				throw new NotImplementedException("ERROR: found undefined field " + value.Name);
			}
			if(ShouldWriteNullCheckCode(value))
				tabString = tabString.Substring(1);
		}

		private  bool HasOperators (XmlNode value) {
			return HasCopyValueAttribute(value) || HasDefaultValueAttribute(value) || HasIncrementValueAttribute(value);
		}

		private  bool IsMandatoryField (XmlNode value) {
			return !HasAttribute(value, "presence") || value.Attributes["presence"].Value == "mandatory";
		}
	}

	public class EnumInfo {
		static string Prefix = "lmc";

		public int Value { get; set; }

		public string EnumName { 
			get;
			set;
		}

		public string EnumFullName { 
			get{ return "LogMessageCode::" + EnumName; }
		}

		public void ParseEnum (string line) {
			string[] tokens = line.Replace(" ", "").Split(new char[] { '=', ',' }, 2);
			if(tokens.Length != 2) {
				Console.WriteLine("error: invalid enum line!");
				throw new ArgumentException();
			}
			EnumName = tokens[0].Trim();
			if(tokens[1].EndsWith(","))
				tokens[1] = tokens[1].Substring(0, tokens[1].Length - 1);
			Value = int.Parse(tokens[1]);
		}

		string messageText;

		public string MessageText { 
			get { return messageText; }
			set {  
				if(MessageText == value)
					return;
				messageText = value;
				if(string.IsNullOrEmpty(EnumName))
					EnumName = GetEnumName();
			}
		}

		string GetEnumName () { 
			if(string.IsNullOrEmpty(MessageText))
				return string.Empty;
			string res = MessageText;

			while(true) {
				if(!char.IsLetterOrDigit(res[res.Length - 1]))
					res = res.Substring(0, res.Length - 1);
				else
					break;
			}

			bool end = false;
			while(!end) {
				end = true;
				foreach(char c in res) {
					if(!char.IsLetterOrDigit(c) && c != '_') {
						res = res.Replace(c, '_');
						end = false;
						break;
					}
				}
			}

			res = res.Replace("____", "_");
			res = res.Replace("___", "_");
			res = res.Replace("__", "_");
		
			res = Prefix + res;
			return res;
		}
	}

	public class TextFile {
		public TextFile () {
			Lines = new List<string>();
			OriginalLines = new List<string>();
		}

		public string FileName { get; set; }

		public bool Modified {
			get{ 
				if(OriginalLines.Count != Lines.Count)
					return true;

				for(int i = 0; i < OriginalLines.Count; i++) {
					if(!string.Equals(Lines[i], OriginalLines[i])) {
						return true;
					}
				}
				return false;
			}
		}
		public int FindString (string searchString) {
			if(Line < 0 || Line > LineCount)
				Line = 0;
			for(int i = Line; i < LineCount; i++) {
				if(Lines[i].Contains(searchString)) {
					Line = i;
					return i;
				}
			}
			Line = -1;
			return -1;
		}

		public bool LoadFromFile (string fileName) {
			FileName = fileName;
			Lines.Clear();
			try {
				StreamReader reader = new StreamReader(fileName);
				string line = null;
				while((line = reader.ReadLine()) != null) {
					Lines.Add(line);
					OriginalLines.Add((string)line.Clone());
				}
				reader.Close();
			} catch(Exception) { 
				return false;
			}
			return true;
		}

		public bool Save () {
			return WriteToFile(FileName);
		}

		bool WriteToFile (string fileName) {
			if(!Modified) {
				//Console.WriteLine(FileName + " was not changed. skip update.");
				return true;
			}
			try {
				StreamWriter writer = new StreamWriter(fileName);
				foreach(string str in Lines)
					writer.WriteLine(str);
				writer.Flush();
				writer.Close();
			} catch(Exception) {
				return false;
			}
			//Modified = false;
			return true;
		}

		public List<string> Lines { get; set; }
		protected List<string> OriginalLines { get; set; }

		public int Line { get; set; }

		public string LineText { get { return Lines[Line]; } }

		public void GoTo (int line) {
			Line = Math.Min(line, Lines.Count - 1);
		}

		public void Replace (int index, string newLine) { 
			//Modified = true;
			Lines[index] = newLine;
		}

		public void Remove (int index) { 
			//Modified = true;
			Lines.RemoveAt(index);
		}

		public void Add (int index, string newLine) {
			//Modified = true;
			Lines.Insert(index, newLine);
		}

		public void Add (string newLine) {
			//Modified = true;
			Lines.Insert(Line, newLine);
			Line++;
		}

		public int LineCount { get { return Lines.Count; } }

		public void SetCurrentLine (string newText) {
			//Modified = true;
			Lines[Line] = newText;
		}

		public void ClearRegion (string regionName) {
			GoTo(0);
			if(FindString(regionName) == -1)
				throw new ArgumentException(regionName + " region not found");
			int startLine = Line + 1;
			int endLine = FindString("endregion");
			if(endLine == -1 || !LineText.Contains("pragma"))
				throw new ArgumentException("pragma region not found");
			for(int i = 0; i < endLine - startLine; i++)
				Lines.RemoveAt(startLine);
			//Console.WriteLine("cleared region '" + regionName + "' removed lines from " + startLine + " to " + endLine);
			Line = startLine;
		}
	}

	class MainClass {
		private static Dictionary<string, string> m_params = new Dictionary<string, string>();

		public static void Main (string[] args) {
			OptionSet p = new OptionSet() { {"x|xml=", "Full path to config XML",
					v => m_params.Add("x", v)
				}, {"d|data=", "Path to directory with data files",
					v => m_params.Add("d", v)
				}, {"o|out=", "Output directory",
					v => m_params.Add("o", v)
				}, {"s|src=", "C++ sources directory",
					v => m_params.Add("s", v)
				}, {"f|fast", "Generate Fast protocol code",
					v => m_params.Add("f", v)
				}, {"ax|asts_xml=", "Path to Asts templates file xml",
					v => m_params.Add("ax", v)
				}, {"sx|spectra_xml=", "Path to Spectra templates file xml",
					v => m_params.Add("sx", v)
				}, {"acfg|asts_cfg=", "Path to asts config file xml",
					v => m_params.Add("acfg", v)
				}, {"scfg|spectra_cfg=", "Path to spectra config file xml",
					v => m_params.Add("scfg", v)
				}, {"fh|fast__source_h=", "Path to FastProtocolManager.h file",
					v => m_params.Add("fh", v)
				}, {"fc|fast__source_cpp=", "Path to FastProtocolManager.cpp file",
					v => m_params.Add("fc", v)
				}, {"ft|fast_types=", "Path to FastTypes.h file",
					v => m_params.Add("ft", v)
				}, {"rb|robot_source_cpp=", "Path to Robot.cpp file",
					v => m_params.Add("rb", v)
				}, {"incCurr|fast_check_const", "Write constant checking code in fast protocol files",
					v => m_params.Add("incCurr", v)
				}
			};
			try {
				p.Parse(args);
			} catch(OptionException e) {
				Console.WriteLine(e.Message);
			}
			//if(!CopyFastServerConfigurationFile()) {
			//	Console.WriteLine("exit.");
			//	return;
			//}

			GenerateLogMessages();
			GenerateFast();
		}
		static void GenerateFast() {
			string value;
			Console.WriteLine("generate fast protocol...");
			if(!m_params.TryGetValue("f", out value)) {
				Console.WriteLine("skip.");
				return;
			}
			FastTemplatesCodeGenerator generator = new FastTemplatesCodeGenerator();
			generator.WriteConstantCheckingCode = m_params.TryGetValue("incCurr", out value);

			if(!m_params.TryGetValue("fc", out value)) {
				Console.WriteLine("FastProtocolManager.cpp file not specified. skip generation.");
				return;
			}
			generator.ManagerSourceFileCpp = value;
			if(!m_params.TryGetValue("fh", out value)) {
				Console.WriteLine("FastProtocolManager.h file not specified. skip generation.");
				return;
			}
			generator.ManagerSourceFileH = value;
			if(!m_params.TryGetValue("ft", out value)) {
				Console.WriteLine("FastTypes file not specified. skip generation.");
				return;
			}
			generator.SourceTypes = value;
			if(!m_params.TryGetValue("ax", out value)) {
				Console.WriteLine("Asts template file not specified. skip generation.");
				return;
			}
			generator.AstsTemplateFile = value;
			if(!m_params.TryGetValue("sx", out value)) {
				Console.WriteLine("Spectra template file not specified. skip generation.");
				return;
			}
			generator.SpectraTemplateFile = value;
			if(!m_params.TryGetValue("rb", out value)) {
				Console.WriteLine("Robot.cpp file not specified. skip generation.");
				return;
			}
			generator.RobotCpp = value;
			if(!m_params.TryGetValue("acfg", out value)) {
				Console.WriteLine("Asts config file not specified. skip generation.");
				return;
			}
			generator.AstsServerConfigFileName = value;
			if(!m_params.TryGetValue("scfg", out value)) {
				Console.WriteLine("Spectra config file not specified. skip generation.");
				return;
			}
			generator.SpectraServerConfigFileName = value;

			if(!generator.Generate()) {
				Console.WriteLine("generate fast protocol - failed.");
				return;
			}
			Console.WriteLine("generate fast protocol - done.");
		}

		static string LogMessageCodes_GeneratedCode = "LogMessageCodes_GeneratedCode";
		static string LogMessagesProvider_InitializeLogMessageText_GeneratedCode = "LogMessagesProvider_InitializeLogMessageText_GeneratedCode";

		public static void GenerateLogMessages () { 
			Console.WriteLine("generate log messages...");
			List<TextFile> files = LoadSourceFiles();
			if(files == null)
				return;

			TextFile enumFile = GetFileWithRegion(LogMessageCodes_GeneratedCode, files);
			TextFile msgInitFile = GetFileWithRegion(LogMessagesProvider_InitializeLogMessageText_GeneratedCode, files);

			if(enumFile == null) {
				Console.WriteLine("error: can't find file containing 'LogMessageCodes_GeneratedCode' region");
				return;
			}
			if(msgInitFile == null) {
				Console.WriteLine("error: can't find file containing 'LogMessagesProvider_InitializeLogMessageText_GeneratedCode' region");
				return;
			}

			List<EnumInfo> availableEnums = GetAvailableEnums(enumFile, msgInitFile);
			//Console.WriteLine("found existing enums " + availableEnums.Count);
			//foreach(EnumInfo info in availableEnums) {
			//	Console.WriteLine("existing enum: " + info.EnumName + " = " + info.Value + " -> " + info.MessageText);
			//}
			int count = availableEnums.Count;
			FindInitializeStringConstants(files, availableEnums);
			if(availableEnums.Count != count) {
				WriteLogMessageCodeEnumDeclaration(enumFile, availableEnums);
				WriteLogMessageTextInitializationCode(msgInitFile, availableEnums);
			}

			foreach(TextFile file in files) {
				if(!file.Modified) {
					//Console.WriteLine(file.FileName + " was not modified. skip save");
					continue;
				}
				if(!file.Save())
					throw new IOException("error: cannot update file " + file.FileName);
			}

			Console.WriteLine("done.");
		}

		public static void WriteLogMessageTextInitializationCode (TextFile file, List<EnumInfo> enums) {
			file.ClearRegion(LogMessagesProvider_InitializeLogMessageText_GeneratedCode);
			foreach(EnumInfo info in enums) {
				string code = "\tthis->m_logMessageText[" + info.EnumFullName + "] = \"" + info.MessageText + "\";";
				file.Add(code);
				//Console.WriteLine(code);
			}
		}

		public static void WriteLogMessageCodeEnumDeclaration (TextFile file, List<EnumInfo> enums) {
			file.ClearRegion(LogMessageCodes_GeneratedCode);
			for(int i = 0; i < enums.Count; i++) {
				string code = "\t" + enums[i].EnumName + " = " + enums[i].Value;
				if(i < enums.Count - 1)
					code += ",";
				file.Add(code);
				//Console.WriteLine(code);
			}
		}

		public static void FindInitializeStringConstants (List<TextFile> files, List<EnumInfo> enums) {
			foreach(TextFile file in files) {
				FindInitializeStringConstants(file, enums);
			}
		}

		public static void FindInitializeStringConstants (TextFile file, List<EnumInfo> enums) {
			for(int i = 0; i < file.LineCount; i++) {
				file.GoTo(i);
				if(!file.LineText.Contains("DefaultLogManager"))
					continue;
				if(!file.LineText.Contains(';'))
					continue;
				if(!file.LineText.Contains("->"))
					continue;
				string[] tokens = file.LineText.Split(new string[] { "::", "->" }, StringSplitOptions.RemoveEmptyEntries);
				if(tokens[1] != "Default")
					continue;
				int index = 0;
				while(true) {
					index = file.LineText.IndexOf('"');
					int endIndex = file.LineText.IndexOf('"', index + 1);
					if(index == -1)
						break;
					if(endIndex == -1)
						break;
					string message = file.LineText.Substring(index, endIndex - index + 1);
					EnumInfo info = new EnumInfo();
					info.MessageText = message.Replace("\"", "");
					info.Value = GetMaxEnumValue(enums) + 1;
					enums.Add(info);
					file.SetCurrentLine(file.LineText.Replace(message, info.EnumFullName)); 
					//Console.WriteLine(file.FileName + ": replaced " + message + " with " + info.EnumFullName);
					index = endIndex + 1;
				}
			}
		}

		public static int GetMaxEnumValue (List<EnumInfo> enums) {
			if(enums.Count == 0)
				return 0;
			return enums.Max(i => i.Value);
		}

		public static List<EnumInfo> GetAvailableEnums (TextFile enumFile, TextFile msgInitFile) {
			List<EnumInfo> res = new List<EnumInfo>();

			enumFile.GoTo(0);
			int startPos = enumFile.FindString(LogMessageCodes_GeneratedCode);
			int endPos = enumFile.FindString("endregion");

			if(startPos == -1) {
				Console.WriteLine("region '" + LogMessageCodes_GeneratedCode + "' was not found");
				return res;
			}
			if(endPos == -1) {
				Console.WriteLine("pragma endregion was not found");
				return res;
			}

			for(int i = startPos + 1; i < endPos; i++) {
				enumFile.GoTo(i);
				EnumInfo info = new EnumInfo();
				info.ParseEnum(enumFile.LineText);
				res.Add(info);
				//Console.WriteLine("found enum value -> " + info.EnumName + " = " + info.Value);
			}

			startPos = msgInitFile.FindString(LogMessagesProvider_InitializeLogMessageText_GeneratedCode);
			endPos = msgInitFile.FindString("endregion");
			// this->LogMessageText[LogMessageCode::lmcSuccess] = "Some String";
			for(int i = startPos + 1; i < endPos; i++) { 
				msgInitFile.GoTo(i);
				string[] tokens = msgInitFile.LineText.Split(new string[] { "->", "=", ";", "[", "::", "]" }, StringSplitOptions.RemoveEmptyEntries);
				if(tokens.Length == 0)
					continue;
				for(int t = 0; t < tokens.Length; t++) {
					tokens[t] = tokens[t].Trim();
				}
				if(tokens[0] != "this" || tokens[1] != "m_logMessageText" || tokens[2] != "LogMessageCode") {
					Console.WriteLine("error: invalid enum initialization string " + msgInitFile.LineText);
					throw new ArgumentException();
				}
				EnumInfo info = GetEnum(res, tokens[3]);
				if(info == null) {
					throw new KeyNotFoundException("Enum initializer not found: '" + tokens[3] + "'  '" + res[0].EnumName + "'");
				}
				int messageStart = msgInitFile.LineText.IndexOf('"');
				int messageEnd = msgInitFile.LineText.LastIndexOf('"');
				if(messageStart == -1 || messageEnd == -1)
					throw new KeyNotFoundException("Enum message text not found: " + tokens[3]);
				info.MessageText = msgInitFile.LineText.Substring(messageStart + 1, messageEnd - messageStart - 1);
				//Console.WriteLine("found enum message text -> '" + info.MessageText + "' for enum " + tokens[3]);
			}

			return res;
		}

		public static EnumInfo GetEnum (List<EnumInfo> enums, string enumName) {
			return enums.FirstOrDefault(item => item.EnumName == enumName);
		}

		public static TextFile GetFileWithRegion (string regionName, List<TextFile> files) {
			foreach(TextFile file in files) {
				//Console.WriteLine("processing file " + file.FileName + " for region " + regionName);
				file.GoTo(0);
				if(file.FindString(regionName) != -1) {
					//Console.WriteLine("region '" + regionName + "' found in " + file.FileName + " line: " + file.Line);
					return file;
				}
			}
			return null;
		}

		public static List<TextFile> LoadSourceFiles () {
			List<string> files = GetSourceFiles();
			List<TextFile> loadedFiles = new List<TextFile>();
			foreach(string fileName in files) {
				TextFile lf = new TextFile();
				if(!lf.LoadFromFile(fileName)) {
					Console.WriteLine("error: loading file " + fileName);
					return null;
				}
				loadedFiles.Add(lf);
			}
			return loadedFiles;
		}

		public static List<string> GetSourceFiles () {
			List<string> sources = new List<string>();
			string sourceDir = "";
			if(!m_params.TryGetValue("s", out sourceDir)) {
				sourceDir = "../../source/";
				Console.WriteLine("Using default source directory: " + sourceDir);
			}
			GetSourceFiles(sourceDir, sources);
			return sources;
		}

		public static void GetSourceFiles (string path, List<string> sources) {
			IEnumerable<string> dirs = Directory.EnumerateDirectories(path);
			IEnumerable<string> files = Directory.EnumerateFiles(path);
			foreach(string fileName in files) {
				if(fileName.EndsWith(".h") ||
				   fileName.EndsWith(".hpp") ||
				   fileName.EndsWith(".cpp") ||
				   fileName.EndsWith(".c"))
					sources.Add(fileName);
			}
			foreach(string dir in dirs) {
				GetSourceFiles(dir, sources);
			}
		}

		static string FastServerConfigurationFile { get; set; }
		public static bool CopyFastServerConfigurationFile () { 
			string fileName = "";
			if(!m_params.TryGetValue("ax", out fileName)) {
				fileName = "asts_config_test.xml";
				Console.WriteLine("Using default XML config: " + fileName);
			}
			string inputPath = "";
			if(!m_params.TryGetValue("d", out inputPath)) {
				inputPath = "../../test/data/";
				Console.WriteLine("Using default data directory: " + inputPath);
			}
			string outputPath = "";
			if(!m_params.TryGetValue("o", out outputPath)) {
				outputPath = "/tmp/";
				Console.WriteLine("Using default output directory: " + outputPath);
			}
			if(File.Exists(outputPath + fileName)) {
				Console.WriteLine("found FAST server configuration file in destination. remove.");
				File.Delete(outputPath + fileName);
			}
			if(File.Exists(inputPath + fileName)) { 
				Console.WriteLine("copy FAST server test configuration file");
				File.Copy(inputPath + fileName, outputPath + fileName);
				FastServerConfigurationFile = outputPath + fileName;
				return true;
			} else {
				Console.WriteLine("error: file " + inputPath + fileName + " does not exist");
				return false;
			}
		}
	}
}
