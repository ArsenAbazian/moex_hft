using System;
using System.IO;
using System.Collections.Generic;
using System.Text;
using System.Linq;
using System.Xml;
using Mono.Options;

namespace prebuild {
	class FastTemplatesCodeGenerator {
		List<string> Strings { get; set; }
		List<string> OriginalStrings { get; set; }

		int WriteIndex { get; set; }

		public bool WriteConstantCheckingCode { get; set; }

		public List<string> EncodeMessages { get; set; }
		public string SourceFile { get; set; }
		public string TemplateFile { get; set; }

		void WriteLine (string line) { 
			Strings.Insert(WriteIndex, line);
			WriteIndex++;
		}

		public bool Generate () {
			if(!File.Exists(SourceFile)) {
				Console.WriteLine("source file '" + SourceFile + "' does not exist.");
				return false;
			}
			if(!File.Exists(TemplateFile)) {
				Console.WriteLine("template xml file'" + TemplateFile + "' does not exist.");
				return false;
			}
			
			XmlDocument doc = new XmlDocument();
			doc.Load(TemplateFile);

			StreamReader hFileRead = new StreamReader(SourceFile);
			Strings = new List<string>();
			OriginalStrings = new List<string>();
			string line = null;
			while((line = hFileRead.ReadLine()) != null) {
				Strings.Add(line);
				OriginalStrings.Add((string)line.Clone());
			}
			hFileRead.Close();

			ClearPreviouseGeneratedCode();

			foreach(XmlNode node in doc.ChildNodes) {
				if(node.Name != "templates")
					continue;
				ParseTemplatesNode(node);
			}

			if(OriginalStrings.Count == Strings.Count) {
				bool equal = true;
				for(int i = 0; i < OriginalStrings.Count; i++) {
					if(!string.Equals(Strings[i], OriginalStrings[i])) {
						equal = false;
						break;
					}
				}
				if(equal) {
					Console.WriteLine("no changes were made. skip update source file.");
					return true;
				}
			}

			StreamWriter hFileWrite = new StreamWriter(SourceFile);
			foreach(string str in Strings)
				hFileWrite.WriteLine(str);
			hFileWrite.Flush();
			hFileWrite.Close();

			return true;
		}

		string Message_Info_Structures_Definition_GeneratedCode = "Message_Info_Structures_Definition_GeneratedCode";
		string Structure_Objects_Declaration_GeneratedCode = "Structure_Objects_Declaration_GeneratedCode";
		string Decode_Method_Pointer_Definition_GeneratedCode = "Decode_Method_Pointer_Definition_GeneratedCode";
		string Decode_Method_Pointer_Arrays_GeneratedCode = "Decode_Method_Pointer_Arrays_GeneratedCode";
		string Decode_Methods_Definition_GeneratedCode = "Decode_Methods_Definition_GeneratedCode";
		string Get_Free_Item_Methods_GeneratedCode = "Get_Free_Item_Methods_GeneratedCode";
		string Encode_Methods_Definition_GeneratedCode = "Encode_Methods_Definition_GeneratedCode";
		string String_Constant_Declaration_GeneratedCode = "String_Constant_Declaration_GeneratedCode";

		private  void ClearPreviouseGeneratedCode () {
			string[] keywords = new string[] { 
				Decode_Method_Pointer_Definition_GeneratedCode,
				Message_Info_Structures_Definition_GeneratedCode,
				Structure_Objects_Declaration_GeneratedCode,
				Decode_Method_Pointer_Arrays_GeneratedCode,
				Get_Free_Item_Methods_GeneratedCode,
				Decode_Methods_Definition_GeneratedCode,
				Encode_Methods_Definition_GeneratedCode,
				String_Constant_Declaration_GeneratedCode
			};
			foreach(string keyword in keywords) {
				int startingIndex = GetKeywordLineIndex(keyword) + 1;
				int endIndex = GetEndRegionLineIndex(startingIndex);
				int count = endIndex - startingIndex;
				for(int i = 0; i < count; i++)
					Strings.RemoveAt(startingIndex);
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
			int index = 0;
			foreach(string str in Strings) {
				if(str.Contains(keyword))
					return index;
				index++;
			}
			return -1;
		}

		List<ConstantStringInfo> ConstantStrings { get; set; }

		private  void ParseTemplatesNode (XmlNode templatesNode) {

			//HeaderTags = CollectHeaderTags(templatesNode);
			WriteEntireMethodAddressArrays(templatesNode);
			WriteStructuresDefinitionCode(templatesNode);
			WriteStructuresDeclarationCode(templatesNode);
			ConstantStrings = GetConstantStrings(templatesNode);
			WriteStringConstantDeclarationCode(templatesNode);
			WriteGetFreeItemCode(templatesNode);

			WriteEncodeMethodsCode(templatesNode);
			WriteHeaderParsingCode(templatesNode);
			WriteDecodeMethodsCode(templatesNode);
			WritePrintMethodsCode(templatesNode);
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
			if(EncodeMessages == null || EncodeMessages.Count == 0) {
				return;
			}
			SetPosition(Encode_Methods_Definition_GeneratedCode);
			List<XmlNode> messages = GetAllMessages(templatesNode);
			foreach(XmlNode message in messages) {
				string msgName = message.PreviousSibling.Value.Trim();
				if(!EncodeMessages.Contains(msgName)) {
					continue;
				}
				WriteEncodeMethodCode(message);
			}
		}

		private  void WriteEncodeMethodCode (XmlNode message) {
			StructureInfo info = new StructureInfo() { NameCore = GetTemplateName(message.PreviousSibling.Value) };
			WriteLine("\tinline void " + info.EncodeMethodName + "(" + info.Name + "* info) {");
			WriteLine("\t\tResetBuffer();");
			WriteLine("\t\tWriteMsgSeqNumber(this->m_sendMsgSeqNo);");
			int presenceByteCount = CalcPresenceMapByteCount(message);
			if(GetMaxPresenceBitCount(message) > 0)
				WriteLine("\t\tWritePresenceMap" + presenceByteCount + "(info->PresenceMap);");
			foreach(XmlNode node in message.ChildNodes) {
				info.Parent = null;
				WriteEncodeValueCode(node, info, "\t\t");
			}
			WriteLine("\t}");
		}

		private void WriteNullValueCode(string tabs, XmlNode value) {
			WriteLine(tabs + "this->WriteNull();");
		}

		private  void WriteEncodeValueCode (XmlNode field, StructureInfo si, string tabs) {
			bool nullCheck = ShouldWriteNullCheckCode(field);
			bool presenceCheck = ShouldWriteCheckPresenceMapCode(field);
			if(presenceCheck) {
				string bracket = nullCheck ? " {" : "";
				string checkPresenceMethodName = HasOptionalPresence(field)? "CheckOptionalFieldPresence": "CheckMandatoryFieldPresence";
				WriteLine(tabs + "if(" + checkPresenceMethodName + "(" + si.InCodeValueName + "->PresenceMap, " + si.InCodeValueName + "->" + PresenceIndexName(field) + "))" + bracket);

				tabs += "\t";
			}
			if(nullCheck) {
				WriteLine(tabs + "if(!" + si.InCodeValueName + "->" + AllowFlagName(field) + ")");
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
			StructureInfo info = new StructureInfo() { InCodeValueName = "(*" + itemInfo + ")", NameCore = si.NameCore + Name(field), IsSequence = true };
			WriteLine(tabs + "WriteUInt32_Mandatory(" + si.InCodeValueName + "->" + Name(field) + "Count);");
			WriteLine(tabs + info.Name + " **" + itemInfo + " = " + si.InCodeValueName + "->" + Name(field) + ";");
			WriteLine(tabs + "for(int i = 0; i < " + si.InCodeValueName + "->" + Name(field) + "Count; i++) {");
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
			List<StructureInfo> structures = GetAllStructureNames(templatesNode);
			foreach(StructureInfo str in structures) {
				WriteLine("\tinline " + str.Name + "* " + str.GetFreeMethodName + "() {");
				if(str.IsSequence) {
					WriteLine("\t\t" + str.Name + " *res = this->" + str.CurrentItemValueName + ";");
					WriteLine("\t\tthis->" + str.CurrentItemValueName + "++;");
					WriteLine("\t\treturn res;");
				} else {
					WriteLine("\t\treturn this->" + str.ValueName + ";");
				}
				WriteLine("\t}");
				WriteLine("");
			}
		}

		public class StructureInfo {
			public string Name {
				get {
					return "Fast" + NameCore + Suffix;
				}
			}

			public string NameCore { get; set; }

			public bool IsSequence { get; set; }

			public string ValueName { 
				get { 
					return "m_" + NameCore.Substring(0, 1).ToLower() + NameCore.Substring(1) + (IsSequence ? "Items" : ""); 
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

			public string EncodeMethodName {
				get { return "Encode" + NameCore + Suffix; }
			}

			public StructureInfo Parent { get; set; }
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
		}

		private  List<StructureInfo> GetAllStructureNames (XmlNode templatesNode) {
			List<StructureInfo> res = new List<StructureInfo>();
			foreach(XmlNode node in templatesNode.ChildNodes) {
				if(node.Name == "template") {
					res.Add(new StructureInfo() { NameCore = GetTemplateName(node.PreviousSibling.Value) });
					GetSequenceStructureNames(GetTemplateName(node.PreviousSibling.Value), node, res);
				}
			}
			return res;
		}

		private  void GetSequenceStructureNames (string parentStructNameCore, XmlNode node, List<StructureInfo> res) {
			foreach(XmlNode field in node.ChildNodes) {
				if(field.Name == "sequence") {
					res.Add(new StructureInfo() { IsSequence = true, NameCore = parentStructNameCore + Name(field) });
					GetSequenceStructureNames(parentStructNameCore + Name(field), field, res);
				}
			}
		}

		private  void WriteStructuresDeclarationCode (XmlNode templatesNode) {
			SetPosition(Structure_Objects_Declaration_GeneratedCode);

			List<StructureInfo> structures = GetAllStructureNames(templatesNode);
			foreach(StructureInfo str in structures) {
				WriteLine("\t" + str.Name + "*\t" + str.ValueName + ";");
			}
			foreach(StructureInfo str in structures) {
				if(str.IsSequence) {
					WriteLine("\tint\t\t" + str.MaxItemCountValueName + ";");
				}
			}

			foreach(StructureInfo str in structures) {
				if(str.IsSequence) {
					WriteLine("\t" + str.Name + "\t\t*" + str.CurrentItemValueName + ";");
				}
			}

			WriteLine("");
			WriteLine("\tvoid InitializeMessageInfo() {");
			foreach(StructureInfo str in structures) {
				if(str.IsSequence) {
					WriteLine("\t\tthis->" + str.ValueName + " = new " + str.Name + "[1024];");
					WriteLine("\t\tmemset(this->" + str.ValueName + ", 0, 1024 * sizeof(" + str.Name + "));");
					WriteLine("\t\tthis->" + str.MaxItemCountValueName + " = 1024;");
					WriteLine("\t\tthis->" + str.CurrentItemValueName + " = this->" + str.ValueName + ";");
				} else {
					WriteLine("\t\tthis->" + str.ValueName + " = new " + str.Name + "();");
					WriteLine("\t\tmemset(this->" + str.ValueName + ", 0, sizeof(" + str.Name + "));");
				}
				WriteLine("");
			}
			WriteLine("\t}");

			WriteLine("");

			WriteLine("\tinline void ResetMessageInfoIndicies() {");
			foreach(StructureInfo str in structures) {
				if(str.IsSequence) {
					WriteLine("\t\tthis->" + str.CurrentItemValueName + " = this->" + str.ValueName + ";");
				}
			}
			WriteLine("\t}");

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
				Console.WriteLine("checking " + tagId);
				for(int j = 1; j < templates.Count; j++) {
					if(i >= templates[j].ChildNodes.Count)
						return headerTags;
					string tagId2 = templates[j].ChildNodes[i].Attributes["id"].Value;
					if(tagId != tagId2) {
						Console.WriteLine("non header tag expected " + tagId + " but found " + tagId2);
						return headerTags;
					}
				}
				Console.WriteLine("add header tag " + templates[0].ChildNodes[i].Attributes["name"].Value);
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
				if(node.Name == "template") {
					ParseTemplateNode(node, GetTemplateName(node.PreviousSibling.Value));
				}
			}
			WriteEntireMethodsCode(templatesNode);
		}

		private void WritePrintMethodsCode(XmlNode templatesNode) {
			foreach(XmlNode node in templatesNode.ChildNodes) {
				if(node.Name == "template") {
					PrintTemplateNode(node, GetTemplateName(node.PreviousSibling.Value));
				}
			}
		}

		private  void WriteStructuresDefinitionCode (XmlNode templatesNode) {
			XmlNode lastComment = null;
			SetPosition(Message_Info_Structures_Definition_GeneratedCode);

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

			WriteLine("");
			//WriteLine("typedef struct _FastHeaderInfo {");
			//List<XmlNode> templates = GetTemplates(templatesNode);
			//WriteSequenceNodeFieldDefinition(templates[0], "", true, true, true, 16);
			//WriteLine("}FastHeaderInfo;");
			//WriteLine("");

			foreach(XmlNode node in templatesNode.ChildNodes) {
				if(node.NodeType == XmlNodeType.Comment) {
					lastComment = node;
					continue;
				}
				if(node.Name == "template") {
					WriteNodeSequenceStructDefinition(node, lastComment == null ? "" : GetTemplateName(lastComment.Value));
					lastComment = null;
				}
			}

			lastComment = null;
			foreach(XmlNode node in templatesNode.ChildNodes) {
				if(node.NodeType == XmlNodeType.Comment) {
					lastComment = node;
					continue;
				}
				if(node.Name == "template") {
					WriteNodeDefinition(node, lastComment == null ? "" : GetTemplateName(lastComment.Value));
					lastComment = null;
				}
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
			SetPosition(Decode_Method_Pointer_Definition_GeneratedCode);
			WriteLine("typedef void* (FastProtocolManager::*FastDecodeMethodPointer)();");

			SetPosition(Decode_Method_Pointer_Arrays_GeneratedCode);
			WriteLine("\tFastDecodeMethodPointer* DecodeMethods;");
			WriteLine("");
			WriteLine("\tvoid InitializeDecodeMethodPointers() {");
			int maxId = CalcMaxTemplateId(templatesNode);
			int minId = CalcMinTemplateId(templatesNode);
			int count = maxId - minId + 1;

			WriteLine("\t\tint ptCount = " + count + ";");
			WriteLine("\t\tthis->DecodeMethods = new FastDecodeMethodPointer[ptCount];");
			WriteLine("\t\tmemset(this->DecodeMethods, 0, sizeof(FastDecodeMethodPointer) * ptCount);");
			WriteLine("");
			WriteLine("\t\tfor(int i = 0; i < " + count + "; i++)");
			WriteLine("\t\t\tthis->DecodeMethods[i] = &FastProtocolManager::DecodeUnsupportedMessage;");
			WriteLine("");
			List<DecodeMessageInfo> methods = GetDecodeMessageMethods(templatesNode);
			foreach(DecodeMessageInfo info in methods) {
				WriteLine("\t\tthis->DecodeMethods[" + info.TemplateId + " - " + minId + "] = &FastProtocolManager::" + info.FullDecodeMethodName + ";");
			}
			WriteLine("");
			WriteLine("\t}");
			WriteLine("");
		}

		private  void SetPosition (string keyword) {
			WriteIndex = GetKeywordLineIndex(keyword) + 1;
		}

		class DecodeMessageInfo {
			public string MsgType;
			public int TemplateId;
			public string FullDecodeMethodName;
		}

		private  void WriteEntireMethodsCode (XmlNode templatesNode) {
			List<string> decodeEntryMethodList = GetDecodeEntryMethodList(templatesNode);
			int minId = CalcMinTemplateId(templatesNode);
			foreach(string mSuffix in decodeEntryMethodList) {
				WriteLine("\tinline void* Decode" + mSuffix + "() {");
				WriteLine("\t\tthis->DecodeHeader();");
				WriteLine("\t\tFastDecodeMethodPointer funcPtr = this->DecodeMethods[this->m_templateId - " + minId + "];");
				WriteLine("\t\treturn (this->*funcPtr)();");
				WriteLine("\t}");
			}
		}

		private  List<DecodeMessageInfo> GetDecodeMessageMethods (XmlNode templatesNode) {
			List<DecodeMessageInfo> res = new List<DecodeMessageInfo>();
			foreach(XmlNode node in templatesNode.ChildNodes) {
				if(node.Name != "template")
					continue;
				DecodeMessageInfo info = new DecodeMessageInfo();
				info.MsgType = node.Attributes["name"].Value.Substring(0, 1);
				info.TemplateId = Int32.Parse(node.Attributes["id"].Value);
				info.FullDecodeMethodName = "Decode" + GetTemplateName(node.PreviousSibling.Value);
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
		private  void WriteNodeSequenceStructDefinition (XmlNode template, string parentName) {
			foreach(XmlNode node in template) {
				string name = parentName + Name(node);

				WriteNodeSequenceStructDefinition(node, name);
				StructureInfo info = new StructureInfo() { NameCore = name, IsSequence = true};

				if(node.Name != "sequence")
					continue;

				WriteLine("typedef struct _" + info.Name + " {");
				WriteSequenceNodeFieldDefinition(node, info.NameCore);
				WriteLine("}" + info.Name + ";");
				WriteLine("");

				definedStructName.Add(name);
			}
		}

		private  void WriteSequenceNodeFieldDefinition (XmlNode node, string parentName) {
			WritePresenceMapDefinition(node);
			foreach(XmlNode field in node) {
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
				WriteAllowFlagAndPresenceMapIndex(field);
			}
		}

		string StuctFieldsSpacing { get{ return "\t\t\t\t\t\t\t"; } }

		private void WriteAllowFlagAndPresenceMapIndex(XmlNode field) {
			if(ShouldWriteNullCheckCode(field)) {
				WriteLine("\tbool" + StuctFieldsSpacing + AllowFlagName(field) + ";");
			}
			if(ShouldWriteCheckPresenceMapCode(field)) {
				WriteLine("\tconst UINT" + StuctFieldsSpacing + PresenceIndexName(field) + " = PRESENCE_MAP_INDEX" + CalcFieldPresenceIndex(field) + ";");
			}			
		} 

		private  void WritePresenceMapDefinition (XmlNode node) {
			//int maxPresenceBitCount = GetMaxPresenceBitCount(node);
			//int maxPresenceMapIntCount = forcedPresenceMapCount != 0? forcedPresenceMapCount: CalcPresenceMapIntCount(maxPresenceBitCount);
			WriteLine("\tUINT64" + StuctFieldsSpacing + "PresenceMap;");
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

		private  void WriteSequence (XmlNode field, string parentName) {
			WriteLine("\tint" + StuctFieldsSpacing + Name(field) + "Count;" + GetCommentLine(field));
			WriteLine("\tFast" + parentName + Name(field) + "ItemInfo* " + Name(field) + "[64];" + GetCommentLine(field));
		}

		private  void WriteByteVectorField (XmlNode field) {
			WriteLine("\tBYTE*" + StuctFieldsSpacing + Name(field) + ";" + GetCommentLine(field));
			WriteLine("\tint" + StuctFieldsSpacing + Name(field) + "Length;");
			if(HasCopyValueAttribute(field)) {
				WriteLine("\tBYTE* " + StuctFieldsSpacing + "Prev" + Name(field) + "; // copy");
				WriteLine("\tint" + StuctFieldsSpacing + "Prev" + Name(field) + "Length;// copy");
			}
		}

		private  void WriteDecimalField (XmlNode field) {
			WriteLine("\tDecimal" + StuctFieldsSpacing + Name(field) + ";" + GetCommentLine(field));
			if(HasCopyValueAttribute(field)) {
				WriteLine("\tDecimal" + StuctFieldsSpacing + "Prev" + Name(field) + "; // copy");
			}
		}

		private  void WriteInt64Field (XmlNode field) {
			WriteLine("\tUINT64" + StuctFieldsSpacing + Name(field) + ";" + GetCommentLine(field));
			if(HasCopyValueAttribute(field)) {
				WriteLine("\tUINT64" + StuctFieldsSpacing + "Prev" + Name(field) + "; // copy");
			}
		}

		private  void WriteUint64Field (XmlNode field) {
			WriteLine("\tUINT64" + StuctFieldsSpacing + Name(field) + ";" + GetCommentLine(field));
			if(HasCopyValueAttribute(field)) {
				WriteLine("\tUINT64" + StuctFieldsSpacing + "Prev" + Name(field) + "; // copy");
			}
		}

		private  void WriteInt32Field (XmlNode field) {
			WriteLine("\tINT32" + StuctFieldsSpacing + Name(field) + ";" + GetCommentLine(field));
			if(HasCopyValueAttribute(field)) {
				WriteLine("\tINT32" + StuctFieldsSpacing + "Prev" + Name(field) + "; // copy");
			}
		}

		private  void WriteUint32Field (XmlNode field) {
			WriteLine("\tUINT32" + StuctFieldsSpacing + Name(field) + ";" + GetCommentLine(field));
			if(HasCopyValueAttribute(field)) {
				WriteLine("\tUINT32" + StuctFieldsSpacing + "Prev" + Name(field) + "; // copy");
			}
		}

		private  void WriteStringDefinition (XmlNode field) {
			WriteLine("\tchar*" + StuctFieldsSpacing + Name(field) + ";" + GetCommentLine(field));
			WriteLine("\tint" + StuctFieldsSpacing + Name(field) + "Length;");
			if(HasCopyValueAttribute(field)) {
				WriteLine("\tchar*" + StuctFieldsSpacing + "Prev" + Name(field) + "; // copy");
				WriteLine("\tint" + StuctFieldsSpacing + "Prev" + Name(field) + "Length; // copy");
			}
		}

		string GetTemplateName (string templateName) {
			templateName = templateName.Replace("-", "");
			templateName = templateName.Replace("/", "");
			templateName = templateName.Replace(" ", "");
			return templateName;
		}

		List<string> definedStructName = new List<string>();

		private  void WriteNodeDefinition (XmlNode node, string templateName) {
			if(definedStructName.Contains(templateName))
				return;
			WriteLine("typedef struct _Fast" + templateName + "Info {");
			WriteSequenceNodeFieldDefinition(node, templateName);
			WriteLine("}Fast" + templateName + "Info;");
			WriteLine("");

			definedStructName.Add(templateName);
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

		private void WriteCopyPresenceMap(string tabs, string infoName, int count) {
			WriteLine(tabs + infoName + "->PresenceMap = this->m_presenceMap;");
		}

		private  void ParseTemplateNode (XmlNode template, string templateName) {
			WriteLine("\tvoid* Decode" + templateName + "() {");
			StructureInfo info = new StructureInfo() { NameCore = templateName };
			WriteLine("\t\tFast" + templateName + "Info* info = " + info.GetFreeMethodName + "();");
			WriteLine("");
			foreach(XmlNode value in template.ChildNodes) {
				ParseValue(value, "info", templateName, "\t\t");
			}
			WriteLine("\t\treturn info;");
			WriteLine("\t}");
		}

		private void WritePrintPresenceMap(XmlNode template, StructureInfo info, string tabs, int tabsCount) {
			if(GetMaxPresenceBitCount(template) > 0) {
				WriteLine(tabs + "PrintPresenceMap(" + info.ValueName + "->PresenceMap, " + GetMaxPresenceBitCount(template) + ", " + tabsCount + ");");
			}
		}

		private  void PrintTemplateNode (XmlNode template, string templateName) {
			StructureInfo info = new StructureInfo() { NameCore = templateName };
			WriteLine("\tvoid Print" + templateName + "(" + info.Name + " *info) {");
			WriteLine("");
			WriteLine("\t\tprintf(\"" + info.Name + " {\");");
			WritePrintPresenceMap(template, info, "\t\t", 1);
			foreach(XmlNode value in template.ChildNodes) {
				PrintValue(value, "info", templateName, "\t\t", 1);
			}
			WriteLine("\t\tprintf(\"}\\n\");");
			WriteLine("\t}");
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

		private  void WriteCopyOperatorCode (XmlNode value, string structName, string parentName, string tabString) {
			WriteLine(tabString + "else {");
			//WriteLine(tabString + "\t" + structName + "->" + Name(value) + "++;");
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

		string Name (XmlNode node) {
			return node.Attributes["name"] != null ? node.Attributes["name"].Value : "";
		}
		string PresenceIndexName(XmlNode node) {
			return Name(node) + "PresenceIndex";
		}
		string AllowFlagName(XmlNode node) {
			return "Allow" + Name(node);
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

		private  void ParseSequence (XmlNode value, string objectValueName, string parentClassCoreName, string tabString) {
			string itemInfo = GetIemInfoPrefix(value) + "ItemInfo";
			WriteLine("");
			WriteLine(tabString + objectValueName + "->" + Name(value) + "Count = ReadUInt32_Mandatory();");
			WriteLine(tabString + "Fast" + parentClassCoreName + Name(value) + "ItemInfo* " + itemInfo + " = NULL;");
			WriteLine("");
			WriteLine(tabString + "for(int i = 0; i < " + objectValueName + "->" + Name(value) + "Count; i++) {");
			WriteLine(tabString + "\t" + itemInfo + " = GetFree" + parentClassCoreName + Name(value) + "ItemInfo();");
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
				ParseValue(node, itemInfo, parentClassCoreName + Name(value), tabString + "\t");
				LevelCount--;
			}
			WriteLine(tabString + "}");
			WriteLine("");
		}

		private  bool ExtendedDecimal (XmlNode value) {
			foreach(XmlNode node in value.ChildNodes)
				if(node.Name == "exponent" || node.Name == "mantissa")
					return true;
			return false;
		}

		private  void ParseByteVectorValue (XmlNode value, string info, string tabString) {
			if(ShouldWriteNullCheckCode(value)) {
				WriteLine(tabString + "if(!CheckProcessNullByteVector())");
				tabString += "\t";
			}
			if(HasOptionalPresence(value))
				WriteLine(tabString + "ReadByteVector_Optional(&(" + info + "->" + Name(value) + "), &(" + info + "->" + Name(value) + "Length)" + ");");
			else
				WriteLine(tabString + "ReadByteVector_Mandatory(&(" + info + "->" + Name(value) + "), &(" + info + "->" + Name(value) + "Length)" + ");");
			if(ShouldWriteNullCheckCode(value)) {
				tabString = tabString.Substring(1);
				if(HasOperators(value)) {
					WriteLine(tabString + "else");
					tabString += "\t";
					WriteByteVectorValueOperatorsCode(value, info, tabString);
					tabString = tabString.Substring(1);
				}
			}
		}

		private  void ParseDecimalValue (XmlNode value, string info, string tabString) {
			if(ShouldWriteNullCheckCode(value)) {
				WriteLine(tabString + "if(!CheckProcessNullDecimal())");
				tabString += "\t";
			}
			if(ExtendedDecimal(value))
				throw new Exception("Extended deciamal detected in template!");
			if(HasOptionalPresence(value))
				WriteLine(tabString + "ReadDecimal_Optional(&(" + info + "->" + Name(value) + "));");
			else
				WriteLine(tabString + "ReadDecimal_Mandatory(&(" + info + "->" + Name(value) + "));");
			if(ShouldWriteNullCheckCode(value)) {
				tabString = tabString.Substring(1);
				if(HasOperators(value)) {
					WriteLine(tabString + "else");
					tabString += "\t";
					WriteDecimalValueOperatorsCode(value, info, tabString);
					tabString = tabString.Substring(1);
				}
			}
		}

		private  void ParseInt64Value (XmlNode value, string info, string tabString) {
			if(ShouldWriteNullCheckCode(value)) {
				WriteLine(tabString + "if(!CheckProcessNullInt64())");
				tabString += "\t";
			}
			if(HasOptionalPresence(value))
				WriteLine(tabString + info + "->" + Name(value) + " = ReadInt64_Optional();");
			else
				WriteLine(tabString + info + "->" + Name(value) + " = ReadInt64_Mandatory();");
			if(ShouldWriteNullCheckCode(value)) {
				tabString = tabString.Substring(1);
				if(HasOperators(value)) {
					WriteLine(tabString + "else");
					tabString += "\t";
					WriteInt64ValueOperatorsCode(value, info, tabString);
					tabString = tabString.Substring(1);
				}
			}
		}

		private  void ParseUint64Value (XmlNode value, string info, string tabString) {
			if(ShouldWriteNullCheckCode(value)) {
				WriteLine(tabString + "if(!CheckProcessNullUInt64())");
				tabString += "\t";
			}
			if(HasOptionalPresence(value))
				WriteLine(tabString + info + "->" + Name(value) + " = ReadUInt64_Optional();");
			else
				WriteLine(tabString + info + "->" + Name(value) + " = ReadUInt64_Mandatory();");
			if(ShouldWriteNullCheckCode(value)) {
				tabString = tabString.Substring(1);
				if(HasOperators(value)) {
					WriteLine(tabString + "else");
					tabString += "\t";
					WriteUint64ValueOperatorsCode(value, info, tabString);
					tabString = tabString.Substring(1);
				}
			}
		}

		private  void ParseInt32Value (XmlNode value, string info, string tabString) {
			if(ShouldWriteNullCheckCode(value)) {
				WriteLine(tabString + "if(!CheckProcessNullInt32())");
				tabString += "\t";
			}
			if(HasOptionalPresence(value))
				WriteLine(tabString + info + "->" + Name(value) + " = ReadInt32_Optional();");
			else
				WriteLine(tabString + info + "->" + Name(value) + " = ReadInt32_Mandatory();");
			if(ShouldWriteNullCheckCode(value)) {
				tabString = tabString.Substring(1);
				if(HasOperators(value)) {
					WriteLine(tabString + "else");
					tabString += "\t";
					WriteInt32ValueOperatorsCode(value, info, tabString);
					tabString = tabString.Substring(1);
				}
			}
		}

		private  void ParseUint32Value (XmlNode value, string info, string tabString) {
			if(ShouldWriteNullCheckCode(value)) {
				WriteLine(tabString + "if(!CheckProcessNullUInt32())");
				tabString += "\t";
			}
			if(HasOptionalPresence(value))
				WriteLine(tabString + info + "->" + Name(value) + " = ReadUInt32_Optional();");
			else
				WriteLine(tabString + info + "->" + Name(value) + " = ReadUInt32_Mandatory();");
			if(ShouldWriteNullCheckCode(value)) {
				tabString = tabString.Substring(1);
				if(HasOperators(value)) {
					WriteLine(tabString + "else");
					tabString += "\t";
					WriteUint32ValueOperatorsCode(value, info, tabString);
					tabString = tabString.Substring(1);
				}
			}
		}

		private  void ParseStringValue (XmlNode value, string info, string tabString) {
			if(ShouldWriteNullCheckCode(value)) {
				WriteLine(tabString + "if(!CheckProcessNullString())");
				tabString += "\t";
			}
			if(HasOptionalPresence(value))
				WriteLine(tabString + "ReadString_Optional(&(" + info + "->" + Name(value) + "), &(" + info + "->" + Name(value) + "Length)" + ");");
			else
				WriteLine(tabString + "ReadString_Mandatory(&(" + info + "->" + Name(value) + "), &(" + info + "->" + Name(value) + "Length)" + ");");
			if(ShouldWriteNullCheckCode(value)) {
				tabString = tabString.Substring(1);
				if(HasOperators(value)) {
					WriteLine(tabString + "else {");
					tabString += "\t";
					WriteStringValueOperatorsCode(value, info, tabString);
					tabString = tabString.Substring(1);
					WriteLine(tabString + "}");
				}
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

		private  void WriteUint32ValueOperatorsCode (XmlNode value, string info, string tabString) {
			if(HasDefaultValueAttribute(value)) {
				WriteUint32ValueDefault(value, info, tabString);
			}
			if(HasCopyValueAttribute(value)) {
				WriteSimplePrevValueAssignCode(value, info, tabString);
			}
			if(HasIncrementValueAttribute(value)) {
				WriteSimpleIncrementValueCode(value, info, tabString);
			}
		}

		private  void WriteInt32ValueOperatorsCode (XmlNode value, string info, string tabString) {
			if(HasDefaultValueAttribute(value)) {
				WriteInt32ValueDefault(value, info, tabString);
			}
			if(HasCopyValueAttribute(value)) {
				WriteSimplePrevValueAssignCode(value, info, tabString);
			}
			if(HasIncrementValueAttribute(value)) {
				WriteSimpleIncrementValueCode(value, info, tabString);
			}
		}

		private  void WriteSimplePrevValueAssignCode (XmlNode value, string info, string tabString) {
			WriteLine(tabString + info + "->" + Name(value) + " = " + info + "->Prev" + Name(value) + ";");
		}

		private  void WriteDecimalValueOperatorsCode (XmlNode value, string info, string tabString) {
			if(HasDefaultValueAttribute(value)) {
				WriteDecimalValueDefault(value, info, tabString);
			}
			if(HasCopyValueAttribute(value)) {
				WriteDecimalCopyOperatorCode(value, info, tabString);
			}
			if(HasIncrementValueAttribute(value))
				throw new Exception("TODO Increment decimal");
		}

		private  void WriteDecimalCopyOperatorCode (XmlNode value, string info, string tabString) {
			WriteLine(tabString + "*((UNT64*)&(" + info + "->" + Name(value) + ")) = *((UINT64*)&(" + info + "->Prev" + Name(value) + "));");
		}

		private  void WriteByteVectorValueOperatorsCode (XmlNode value, string info, string tabString) {
			if(HasCopyValueAttribute(value)) {
				WriteSimplePrevValueAssignCode(value, info, tabString);
			}
		}

		private  void WriteInt64ValueOperatorsCode (XmlNode value, string info, string tabString) {
			if(HasDefaultValueAttribute(value)) {
				WriteInt64ValueDefault(value, info, tabString);
			}
			if(HasCopyValueAttribute(value)) {
				WriteSimplePrevValueAssignCode(value, info, tabString);
			}
			if(HasIncrementValueAttribute(value)) {
				WriteSimpleIncrementValueCode(value, info, tabString);
			}
			if(HasIncrementValueAttribute(value)) {
				WriteSimpleIncrementValueCode(value, info, tabString);
			}
		}

		private  void WriteUint64ValueOperatorsCode (XmlNode value, string info, string tabString) {
			if(HasDefaultValueAttribute(value)) {
				WriteUint64ValueDefault(value, info, tabString);
			}
			if(HasCopyValueAttribute(value)) {
				WriteSimplePrevValueAssignCode(value, info, tabString);
			}
			if(HasIncrementValueAttribute(value)) {
				WriteSimpleIncrementValueCode(value, info, tabString);
			}
		}

		private  void WriteSimpleIncrementValueCode (XmlNode value, string info, string tabString) {
			WriteLine(tabString + info + "->" + Name(value) + "++;");
		}

		private  void WriteStringValueOperatorsCode (XmlNode value, string info, string tabString) {
			if(HasDefaultValueAttribute(value)) { 
				WriteStringValueDefault(value, info, tabString);
			} else if(HasCopyValueAttribute(value)) {
				WriteStringCopyValueCode(value, info, tabString);
			}
		}

		private  void WriteStringCopyValueCode (XmlNode value, string info, string tabString) {
			WriteLine(tabString + info + "->" + Name(value) + " = " + info + "->Prev" + Name(value) + ";");
			WriteLine(tabString + info + "->" + Name(value) + "Length = " + info + "->Prev" + Name(value) + "Length;");
		}

		private  void ParseValue (XmlNode value, string objectValueName, string classCoreName, string tabString) {
			if(value.Name == "length")
				return;
			bool shouldWritePmapCode = ShouldWriteCheckPresenceMapCode(value);

			// skip constant value WHY??????!!!!!
			if(HasConstantAttribute(value))
				return;

			if(shouldWritePmapCode) {
				WriteCheckingPresenceMapCode(value, objectValueName, classCoreName, tabString);
				tabString += "\t";
			}
			if(value.Name == "string")
				ParseStringValue(value, objectValueName, tabString);
			else if(value.Name == "uInt32")
				ParseUint32Value(value, objectValueName, tabString);
			else if(value.Name == "int32")
				ParseInt32Value(value, objectValueName, tabString);
			else if(value.Name == "uInt64")
				ParseUint64Value(value, objectValueName, tabString);
			else if(value.Name == "int64")
				ParseInt64Value(value, objectValueName, tabString);
			else if(value.Name == "decimal")
				ParseDecimalValue(value, objectValueName, tabString);
			else if(value.Name == "byteVector")
				ParseByteVectorValue(value, objectValueName, tabString);
			else if(value.Name == "sequence")
				ParseSequence(value, objectValueName, classCoreName, tabString);
			else {
				WriteLine(tabString + "TODO!!!!!!!!");
				Console.WriteLine("ERROR: found undefined field " + value.Name);
				throw new NotImplementedException("ERROR: found undefined field " + value.Name);
			}
			if(HasConstantAttribute(value))
				WriteConstantValueCheckingCode(value, objectValueName, classCoreName, tabString);
			if(shouldWritePmapCode) {
				tabString = tabString.Substring(1);
				WriteLine(tabString + "}");
				if(IsMandatoryField(value)) {
					WriteOperatorsCode(value, objectValueName, classCoreName, tabString);   
				}
			}
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
			WriteLine(tabString + "PrintByteVector(\"" + Name(value) + "\", " + info + "->" + Name(value) + ", " + info + "->" + Name(value) + "Length" + ", " + tabsCount + ");");
		}

		private  void PrintSequence (XmlNode value, string objectValueName, string parentClassCoreName, string tabString, int tabsCount) {
			string itemInfo = GetIemInfoPrefix(value) + "ItemInfo";
			WriteLine("");
			string countField = objectValueName + "->" + Name(value) + "Count";

			WriteLine(tabString + "Fast" + parentClassCoreName + Name(value) + "ItemInfo* " + itemInfo + " = NULL;");
			WriteLine("");
			WriteLine(tabString + "for(int i = 0; i < " + countField + "; i++) {");
			WriteLine(tabString + "\t" + itemInfo + " = " + objectValueName + "->" + Name(value) + "[i];");

			foreach(XmlNode node in value.ChildNodes) {
				if(node.Name == "length")
					continue;
				LevelCount++;
				tabsCount++;
				PrintValue(node, itemInfo, parentClassCoreName + Name(value), tabString + "\t", tabsCount);
				tabsCount--;
				LevelCount--;
			}
			WriteLine(tabString + "}");
			WriteLine("");
		}

		private  void PrintValue (XmlNode value, string objectValueName, string classCoreName, string tabString, int tabsCount) {
			if(value.Name == "length")
				return;
			
			// skip constant value WHY??????!!!!!
			if(HasConstantAttribute(value))
				return;

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
		}

		private  void WriteOperatorsCode (XmlNode value, string objectValueName, string classCoreName, string tabString) {
			if(!HasOperators(value))
				return;
			WriteLine(tabString + "else {");
			tabString += "\t";
			if(value.Name == "string")
				WriteStringValueOperatorsCode(value, objectValueName, tabString);
			else if(value.Name == "uInt32")
				WriteUint32ValueOperatorsCode(value, objectValueName, tabString);
			else if(value.Name == "int32")
				WriteInt32ValueOperatorsCode(value, objectValueName, tabString);
			else if(value.Name == "uInt64")
				WriteUint64ValueOperatorsCode(value, objectValueName, tabString);
			else if(value.Name == "int64")
				WriteInt64ValueOperatorsCode(value, objectValueName, tabString);
			else if(value.Name == "decimal")
				WriteDecimalValueOperatorsCode(value, objectValueName, tabString);
			tabString = tabString.Substring(1);
			WriteLine(tabString + "}");
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
		}

		public string FileName { get; set; }

		public bool Modified  { get; private set; }

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
				while((line = reader.ReadLine()) != null)
					Lines.Add(line);
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
			Modified = false;
			return true;
		}

		protected List<string> Lines { get; set; }

		public int Line { get; set; }

		public string LineText { get { return Lines[Line]; } }

		public void GoTo (int line) {
			Line = Math.Min(line, Lines.Count - 1);
		}

		public void Replace (int index, string newLine) { 
			Modified = true;
			Lines[index] = newLine;
		}

		public void Remove (int index) { 
			Modified = true;
			Lines.RemoveAt(index);
		}

		public void Add (int index, string newLine) {
			Modified = true;
			Lines.Insert(index, newLine);
		}

		public void Add (string newLine) {
			Modified = true;
			Lines.Insert(Line, newLine);
			Line++;
		}

		public int LineCount { get { return Lines.Count; } }

		public void SetCurrentLine (string newText) {
			Modified = true;
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
				}, {"fx|fast_xml=", "Path to Fast templates file xml",
					v => m_params.Add("fx", v)
				}, {"fs|fast_source=", "Path to FastProtocolManager h file",
					v => m_params.Add("fs", v)
				}, {"fcc|fast_check_const", "Write constant checking code in fast protocol files", 
					v => m_params.Add("fcc", v)
				}, {"fwe|fast_write_encode=", "Write encdode methods for messages",
					v => m_params.Add("fwe", v)
				}
			};
			try {
				p.Parse(args);
			} catch(OptionException e) {
				Console.WriteLine(e.Message);
			}
			foreach(string k in m_params.Keys) {
				Console.WriteLine(k + " " + m_params[k]);
			}
			if(!CopyFastServerConfigurationFile()) {
				Console.WriteLine("exit.");
				return;
			}
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
			generator.WriteConstantCheckingCode = m_params.TryGetValue("fcc", out value);

			if(!m_params.TryGetValue("fs", out value)) {
				Console.WriteLine("FastProtocolManager file not specified. skip generation.");
				return;
			}
			generator.SourceFile = value;
			if(!m_params.TryGetValue("fx", out value)) {
				Console.WriteLine("Fast template file not specified. skip generation.");
				return;
			}
			generator.TemplateFile = value;
			if(m_params.TryGetValue("fwe", out value)) {
				generator.EncodeMessages = new List<string>();
				string[] messages = value.Split(',');
				generator.EncodeMessages.AddRange(messages);
			}

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

		public static bool CopyFastServerConfigurationFile () { 
			string fileName = "";
			if(!m_params.TryGetValue("x", out fileName)) {
				fileName = "config_test.xml";
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
				return true;
			} else {
				Console.WriteLine("error: cannot copy FAST server test configuration file");
				return false;
			}
		}
	}
}
